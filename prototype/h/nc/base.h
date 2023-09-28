#include <stdint.h>
#include <stddef.h>


//# macros are used instead of typedef, because
//typedef types have their own method sets.
//since NashC typenames can only be a single symbol,
//we still use typedefs from stdint.h in most cases

#U8  uint8_t
#U16 uint16_t
#U32 uint32_t
#S8  int8_t
#S16 int16_t
#S32 int
#F32 float
#F64 double
#U64 uint64_t
#S64 int64_t
#bool int

typedef void *pvoid;

class !MGrp;

#LIKELY(x) __builtin_expect(!!(x), 1)
#UNLIKELY(x) __builtin_expect(!!(x), 0)

#inline static __attribute__((always_inline)) #:{inline}
#NOINLINE __attribute__ ((noinline))


#ALIGN(N) __attribute__ ((aligned(N)))
#PACKED __attribute__((packed))

//declaring a pointer RESTRICT, we guarantee compiler,
//that no other pointer will be used to modify the pointed data.
//so compiler could keep more stuff in memory,
//instead of immediately writing back.
#RESTRICT restrict
//#RESTRICT __restrict__

#NC_MALLOC malloc
#NC_FREE free

#MIN(x,y) ((x)<(y)?(x):(y))
#MAX(x,y) ((x)>(y)?(x):(y))


#SWAP(x,y) do {auto t_ = x; x = y; y = t_;} while(0)

//#LIKELY(x) (x)
//#UNLIKELY(x) (x)

#IntGetSetBit(type,utype) {
inline int type."[]"(int bit) {
  return (((utype)*this)>>bit)&1;
}
inline type &type."[]="(int bit, int val) {
  uint32_t sb = (utype)1<<bit;
  *this = ((utype)*this & ~((utype)1<<bit)) | ((utype)val << bit);
  return this;
}}

//allows accessing individual bits in an integer, using []
IntGetSetBit(S8,U8)
IntGetSetBit(U8,U8)
IntGetSetBit(S16,U16)
IntGetSetBit(U16,U16)
IntGetSetBit(S32,U32)
IntGetSetBit(U32,U32)
IntGetSetBit(S64,U64)
IntGetSetBit(U64,U64)

//if you want integer type with alternative [] sematics
//just typedef it. I.e.:
//typedef int entity;
//type &entity."[]"(key_type key) {...}

#:clamp
