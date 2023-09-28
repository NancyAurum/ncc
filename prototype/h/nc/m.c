#include <stdio.h>
#include <stdlib.h>

#:m

struct MHead;
typedef struct MHead MHead;

//FIXME: objects should have an optional destructor function pointer
typedef struct MHead {
  MHead *next; //next object in this group
  MHead *prev; //prev object for fast unlinking
} MHead;

typedef struct MGrp {
  U32 flags;
  MHead list;  //the list of group objects
} MGrp;

#M_GRP_STACK_DEPTH 1024
static MGrp *m_grp_stack[M_GRP_STACK_DEPTH];
static MGrp *m_grp = 0; //current group;
static U32 m_grp_sp = 0;

#M_GRP_TMP 0x01

MGrp *mGrp() {
  MGrp *grp = (MGrp *)malloc(sizeof(MGrp));
  grp->flags = 0;
  grp->list.next = 0;
  grp->list.prev = 0;
  return grp;
}

MGrp *mCurGrp() {
  if (!m_grp) m_grp = mGrp();
  return m_grp;
}

void *mAlloc(size_t size) {
  if (!m_grp) m_grp = mGrp();
  MHead *h = (MHead*)malloc(sizeof(MHead)+size);
  h->prev = &m_grp->list;
  MHead *next = m_grp->list.next;
  h->next = next;
  if (next) next->prev = h;
  m_grp->list.next = h;
  return h+1;
}

void mFree(void *ptr) {
  MHead *h = (MHead*)ptr - 1;
  if (h->prev) {
    h->prev->next = h->next;
    if (h->next) h->next->prev = h->prev;
  }
  free(h);
}

void mFreeGrp(MGrp *grp) {
  if (!grp) grp = m_grp;
  int bottom = (grp == m_grp && m_grp_sp == 0);
  if (grp == m_grp) mEnd();
  mClean(grp);
  if (!bottom) free(grp);
}

void mClean(MGrp *grp) {
  if (!grp) grp = m_grp;
  MHead *h, *next;
  for (h = grp->list.next; h; h = next) {
    next = h->next;
    free(h);
  }
  grp->list.next = 0;
}

void mBegin(MGrp *grp) {
  if (!grp) {
    //fixme: have a pool of pre-allocated groups
    //       since this routine gets called frequently
    grp = mGrp();
    grp->flags |= M_GRP_TMP;
  }
  m_grp_stack[m_grp_sp++] = m_grp;
  m_grp = grp;
}

void mEnd() {
  if (!m_grp_sp) {
    return; //FIXME: this is an errr on user part and should be reported
  }

  MGrp *grp = m_grp;
  m_grp = m_grp_stack[--m_grp_sp];

  if (grp->flags&M_GRP_TMP) mFreeGrp(grp); //temporary group
}

void mDebug() {
  printf("m_grp_sp: %d\n", m_grp_sp);
  printf("m_grp: %p\n", (void*)m_grp);
}

MGrp *mGetGrp(void *ptr) {
  MHead *h = (MHead*)ptr - 1;
  if (!h->prev) return 0; //no group
  while (h->prev) h = h->prev;
  return (MGrp*)h;
}

void *mSetGrp(void *ptr, MGrp *grp) {
  MHead *h = (MHead*)ptr - 1;
  if (h->prev) {
    h->prev->next = h->next;
    if (h->next) h->next->prev = h->prev;
  }
  if (!grp) {
    h->prev = 0;
    h->next = 0;
    return ptr;
  }
  h->prev = &grp->list;
  MHead *next = grp->list.next;
  h->next = next;
  if (next) next->prev = h;
  grp->list.next = h;
  return ptr;
}

void mUnmanage(MGrp *grp) {
  if (!grp) grp = m_grp;
  MHead *h, *next;
  for (h = grp->list.next; h; h = next) {
    next = h->next;
    h->next = 0;
    h->prev = 0;
  }
  grp->list.next = 0;
}
