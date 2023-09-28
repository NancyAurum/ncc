#:base

#include <nc/murmur.h>

//FIXME: allow user to seed the hash with a random number
//       to make it predictable/unpredictable

inline U32 ncHash(void *in, U32 len) {
  return PMurHash32(0xdeadbeef, in, len);
}

inline U32 char.hash {return ncHash(this,strlen(this));}
inline U32 int.hash {return ncHash(this, 4);}
