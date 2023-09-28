#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#:base
#:hash

//initial table size
#HSH_INIT_SZ   (1<<2)

//determines when the table needs to grow
#HSH_NEEDS_GROW(hsh) m_used >= ((m_cap+1)>>2)*3
//#HSH_NEEDS_GROW(hsh) m_used >= ((m_cap+1)>>1)
//#HSH_NEEDS_GROW(hsh) m_used >= ((m_cap+1)>>2)


inline char *char.thsh_nil {return 0;}
inline int char.thsh_is_nil {return this != 0;}
inline int int.thsh_nil {return INT32_MIN;}
inline int int.thsh_is_nil {return *this != INT32_MIN;}


#THsh_(type,key_type,elt_type,hsh) {
class type {
  key_type *m_keys;
  U32 m_cap; //capacity
  U32 m_used;
  elt_type *m_elts;
}
inline void *type.zmalloc_(size_t size) {
  void *p = NC_MALLOC(size);
  memset(p, 0, size);
  return p;
}
inline key_type *type.kmalloc_(U32 size) {
  key_type *p = (key_type*)NC_MALLOC(sizeof(key_type)*size);
  for (U32 i = 0; i < size; i+=4) {
    p[i  ] = p[0].thsh_nil;
    p[i+1] = p[0].thsh_nil;
    p[i+2] = p[0].thsh_nil;
    p[i+3] = p[0].thsh_nil;
  }
  return p;
}
CTOR(type) {
  m_used = 0;
  m_cap = HSH_INIT_SZ-1;
  m_keys = hsh.kmalloc_(HSH_INIT_SZ);
  m_elts = (elt_type *)hsh.zmalloc_(sizeof(m_elts[0])*HSH_INIT_SZ);
}
DTOR(type) {
  if (!m_cap) return;
  NC_FREE(m_keys);
  NC_FREE(m_elts);
  m_cap = 0;
  m_used = 0;
}
inline elt_type *type.get(key_type key) {
  U32 sz = m_cap;
  if (!sz) return 0;
  U32 i = key.hash&sz;
  for ( ; m_keys[i].thsh_is_nil; i = (i+1)&sz) {
    if (m_keys[i].eq(key)) {
      return &m_elts[i];
    }
  }
  return 0;
}
inline elt_type *type.add_(key_type key, int *old) {
  U32 sz = m_cap;
  U32 i = key.hash&sz;
  for ( ; ; i = (i+1)&sz) {
    if (!m_keys[i].thsh_is_nil) {
      m_keys[i] = key;
      m_used++;
      if (old) *old = 0;
      return &m_elts[i];
    }
    if (m_keys[i].eq(key)) {
      if (old) *old = 1;
      return &m_elts[i];
    }
  }
  return 0;
}
static void type.grow {
  if (!m_cap) {
    hsh.ctor;
    return;
  }
  U32 size = m_cap+1;
  U32 new_size = size*2;
  key_type *okeys = m_keys;
  elt_type *oelts = m_elts;
  m_keys = hsh.kmalloc_(new_size);
  m_elts = hsh.zmalloc_(sizeof(m_elts[0])*new_size);
  m_cap = new_size-1;
  m_used = 0;
  for (int i = 0; i < size; i++) {
    if (!okeys[i].thsh_is_nil) continue;
    *hsh.add_(okeys[i],0) = oelts[i];
  }
  NC_FREE(okeys);
  NC_FREE(oelts);
}
inline elt_type *type.add(key_type key, int *old) {
  if (HSH_NEEDS_GROW(hsh)) hsh.grow;
  return hsh.add_(key,old);
}
inline void type.set(key_type key, elt_type value) {
  *hsh.add(key,0) = value;
}
inline int type.collides(key_type key) {
  U32 sz = m_cap;
  if (!sz) return 0;
  U32 i = key.hash&sz;
  if (!m_keys[i].thsh_is_nil) return 0;
  if (m_keys[i].eq(key)) return 0;
  int collisions = 0;
  for ( ; m_keys[i].thsh_is_nil; i = (i+1)&sz) {
    if (m_keys[i].eq(key)) break;
    else collisions++;
  }
  return collisions;
}
inline void type.erase(key_type key) {
  U32 sz = m_cap;
  if (!sz) return;
  U32 i = key.hash&sz;
  for ( ; m_keys[i].thsh_is_nil; i = (i+1)&sz) {
    if (m_keys[i].eq(key)) {
      m_keys[i] = m_keys[0].thsh_nil;
      m_used--;
      i = (i+1)&sz;
      break;
    }
  }
  for ( ; m_keys[i].thsh_is_nil; i = (i+1)&sz) {
    int old;
    elt_type *r = hsh.add_(m_keys[i],&old);
    if (r && !old) {
      *r = m_elts[i];
      m_keys[i] = m_keys[0].thsh_nil;
      m_used--;
      break;
    }
  }
}
inline key_type *type.keys { return m_keys; }
inline U32 type.size { return m_cap; }
inline U32 type.used { return m_used; }
inline elt_type *type.elts { return m_elts; }
} //THsh_

#THsh(type,key_type,elt_type) THsh_(type,key_type,elt_type,this)

#hsh_for(k,v,hsh,{body}) {
  for (U32 i_ = 0, j_; i_ <= (hsh).m_cap; i_++)
    if ((hsh).m_keys[i_].thsh_is_nil) {
      auto &k=(hsh).m_keys[i_];
      auto &v=(hsh).m_elts[i_];
      {body}
    }
}


#if 0

static char *months[] = {
   "jan","feb","mar","apr"
  ,"may","jun","jul","aug"
  ,"sep","oct","nov","dec"
  ,0
};

THsh(CHsh,char*,int)

void hsh_test() {
  CHsh h;

  printf("______POPULATING_____\n");
  for (int i = 0; months[i]; i++) {
    printf("adding %s = %d\n", months[i], i+1);
    h.set(months[i],i+1);
  }

  h.erase("jul");
  h.erase("may");
  h.erase("sep");

  printf("______RETRIEVED______\n");
  for (int i = 0; i < 12; i++) {
    int *r = h.get(months[i]);
    if (r) printf("%s = %d\n", months[i], *r);
  }
  printf("________TABLE________\n");
  printf("size=%d/%d\n", h.used, h.size);

  hsh_for(k,v,h) {
    printf("%s = %d\n", k, v);
  }
}
   
#endif
