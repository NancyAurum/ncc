#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#:base
#:file

#NC_LST_INIT_SZ 4


#TLst_(type,elt_type,lst) {
class type {
  elt_type *m_elts;
  U32 m_tsize;
  U32 m_used;
}
inline elt_type *type.elts { return m_elts; }
inline U32 type.len { return m_used; }
inline U32 type.total_size { return m_tsize; }
inline void type.init(int sz) {
  m_used = 0;
  m_tsize = sz;
  m_elts = (elt_type *)NC_MALLOC(sizeof(m_elts[0])*sz);
}
inline void type.free {
  if (!m_tsize) return;
  NC_FREE(m_elts);
  m_used = 0;
  m_tsize = 0;
  m_elts = 0;
}
CTOR(type) { m_tsize=0; m_used=0; }
DTOR(type) { this.free; }
static void type.grow {
  if (!m_tsize) {
    lst.init(NC_LST_INIT_SZ);
    return;
  }
  U32 new_size = m_tsize*2;
  size_t alcsz = sizeof(m_elts[0])*new_size;
  elt_type *new_elts = (elt_type *)NC_MALLOC(alcsz);
  memcpy(new_elts,m_elts,sizeof(m_elts[0])*(size_t)m_tsize);
  NC_FREE(m_elts);
  m_elts = new_elts;
  m_tsize = (U32)new_size;
}
inline U32 type.reserve() {
  if (m_used==m_tsize) lst.grow;
  return m_used++;
}
inline elt_type *type.add {
  U32 i = lst.reserve;
  return &m_elts[i];
}
inline elt_type type.get(U32 i) {
  return m_elts[i];
}
inline elt_type *type.ref(U32 i) {
  return &m_elts[i];
}
inline elt_type &type."[]"(U32 i) {
  return &m_elts[i];
}
inline elt_type *type.eref(U32 i) {
  while (m_tsize <= i) lst.grow;
  return &m_elts[i];
}
inline void type.push(elt_type value) {
  *lst.add = value;
}
inline elt_type type.pop {
  return m_elts[--m_used];
}
inline elt_type *type.top {
  return &m_elts[m_used-1];
}
inline void type.copy(type *src) {
  this.free;
  this.init(src->m_tsize);
  m_used = src->m_used;
  size_t elts_sz = sizeof(m_elts[0])*(size_t)m_used;
  memcpy(m_elts, src->m_elts, elts_sz);
}
inline void type.serialize(CFile &out) {
  out.write(&m_tsize, 4);
  out.write(&m_used, 4);
  size_t elts_sz = sizeof(m_elts[0])*(size_t)m_used;
  out.write(m_elts, elts_sz);
}
inline int type.deserialize(CFile &in) {
  int r = 0;
  U32 size, used;
  lst.free;
  r += in.read(&size, 4);
  r += in.read(&used, 4);
  lst.init(used);
  m_used = used;
  size_t elts_sz = sizeof(m_elts[0])*(size_t)used;
  r += in.read(m_elts, elts_sz);
  return r;
}
} //TLst_


#foreach(x,xs,{body}) {
  for (int i_ = 0, sz_=(xs).len; i_ < sz_; i_++) {
    auto x = (xs)[i_];
    {body}
  }
}

#TLst(type,elt_type) TLst_(type,elt_type,this)


TLst(S8s,S8)
TLst(U8s,U8)
TLst(S16s,S16)
TLst(U16s,U16)
TLst(S32s,S32)
TLst(U32s,U32)
TLst(S64s,S64)
TLst(U64s,U64)
TLst(F32s,F32)
TLst(F64s,F64)
TLst(CStrs,char*)
TLst(PtrList,pvoid)

U8s CFile.readU8s(int len);
U16s CFile.readU16s(int len);
U32s CFile.readU32s(int len);
S8s CFile.readS8s(int len);
S16s CFile.readS16s(int len);
S32s CFile.readS32s(int len);

  
#if 0
char *string = "hello world this is a test";
auto words = string.split(' ');
for (int i = 0; i < words->used; i++) say(words->elts[i]);
#endif


#if 0
static char *months[] = {
   "jan","feb","mar","apr"
  ,"may","jun","jul","aug"
  ,"sep","oct","nov","dec"
  ,0
};


void cxt_test() {
  CStrs xs;

  printf("______POPULATING_____\n");
  for (int i = 0; months[i]; i++) {
    printf("adding %s (%d)\n", months[i], i);
    xs.push(months[i]);
  }

  printf("______RETRIEVED______\n");
  foreach(x, &xs) {
    printf("%d: %s\n", i_, *x);
  }
  printf("________TABLE________\n");
  printf("size=%d/%d\n", xs.used, xs.size);
}

#endif
