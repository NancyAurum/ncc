#ifndef MURMUR_HASH_H
#define MURMUR_HASH_H
/*-----------------------------------------------------------------------------
 * MurmurHash3 was written by Austin Appleby, and is placed in the public
 * domain.
 *
 * This implementation was written by Shane Day, and is also public domain.
 *
 * This is a portable ANSI C implementation of MurmurHash3_x86_32 (Murmur3A)
 * with support for progressive processing.
 */

/*-----------------------------------------------------------------------------
 
If you want to understand the MurmurHash algorithm you would be much better
off reading the original source. Just point your browser at:
http://code.google.com/p/smhasher/source/browse/trunk/MurmurHash3.cpp


What this version provides?

1. Progressive data feeding. Useful when the entire payload to be hashed
does not fit in memory or when the data is streamed through the application.
Also useful when hashing a number of strings with a common prefix. A partial
hash of a prefix string can be generated and reused for each suffix string.

2. Portability. Plain old C so that it should compile on any old compiler.
Both CPU endian and access-alignment neutral, but avoiding inefficient code
when possible depending on CPU capabilities.

3. Drop in. I personally like nice self contained public domain code, making it
easy to pilfer without loads of refactoring to work properly in the existing
application code & makefile structure and mucking around with licence files.
Just copy PMurHash.h and PMurHash.c and you're ready to go.


How does it work?

We can only process entire 32 bit chunks of input, except for the very end
that may be shorter. So along with the partial hash we need to give back to
the caller a carry containing up to 3 bytes that we were unable to process.
This carry also needs to record the number of bytes the carry holds. I use
the low 2 bits as a count (0..3) and the carry bytes are shifted into the
high byte in stream order.

To handle endianess I simply use a macro that reads a uint32_t and define
that macro to be a direct read on little endian machines, a read and swap
on big endian machines, or a byte-by-byte read if the endianess is unknown.

-----------------------------------------------------------------------------*/

#define MUR_INLINE static inline

/* MSVC warnings we choose to ignore */
#if defined(_MSC_VER)
  #pragma warning(disable: 4127) /* conditional expression is constant */
#endif

/*-----------------------------------------------------------------------------
 * Endianess, misalignment capabilities and util macros
 *
 * The following 3 macros are defined in this section. The other macros defined
 * are only needed to help derive these 3.
 *
 * MUR_READ_UINT32(x)   Read a little endian unsigned 32-bit int
 * MUR_UNALIGNED_SAFE   Defined if MUR_READ_UINT32 works on non-word boundaries
 * MUR_ROTL32(x,r)      Rotate x left by r bits
 */

/* Convention is to define MUR__BYTE_ORDER == to one of these values */
#if !defined(MUR__BIG_ENDIAN)
  #define MUR__BIG_ENDIAN 4321
#endif
#if !defined(MUR__LITTLE_ENDIAN)
  #define MUR__LITTLE_ENDIAN 1234
#endif

/* I386 */
#if defined(_M_IX86) || defined(__i386__) || defined(__i386) || defined(i386)
  #define MUR__BYTE_ORDER MUR__LITTLE_ENDIAN
  #define MUR_UNALIGNED_SAFE
#endif

/* gcc 'may' define MUR__LITTLE_ENDIAN__ or MUR__BIG_ENDIAN__ to 1 (Note the trailing __),
 * or even _LITTLE_ENDIAN or _BIG_ENDIAN (Note the single _ prefix) */
#if !defined(MUR__BYTE_ORDER)
  #if defined(MUR__LITTLE_ENDIAN__) && MUR__LITTLE_ENDIAN__==1 || defined(_LITTLE_ENDIAN) && _LITTLE_ENDIAN==1
    #define MUR__BYTE_ORDER MUR__LITTLE_ENDIAN
  #elif defined(MUR__BIG_ENDIAN__) && MUR__BIG_ENDIAN__==1 || defined(_BIG_ENDIAN) && _BIG_ENDIAN==1
    #define MUR__BYTE_ORDER MUR__BIG_ENDIAN
  #endif
#endif

/* gcc (usually) defines xEL/EB macros for ARM and MIPS endianess */
#if !defined(MUR__BYTE_ORDER)
  #if defined(__ARMEL__) || defined(__MIPSEL__)
    #define MUR__BYTE_ORDER MUR__LITTLE_ENDIAN
  #endif
  #if defined(__ARMEB__) || defined(__MIPSEB__)
    #define MUR__BYTE_ORDER MUR__BIG_ENDIAN
  #endif
#endif

/* Now find best way we can to MUR_READ_UINT32 */
#if MUR__BYTE_ORDER==MUR__LITTLE_ENDIAN
  /* CPU endian matches murmurhash algorithm, so read 32-bit word directly */
  #define MUR_READ_UINT32(ptr)   (*((uint32_t*)(ptr)))
#elif MUR__BYTE_ORDER==MUR__BIG_ENDIAN
  /* TODO: Add additional cases below where a compiler provided bswap32 is available */
  #if defined(__GNUC__) && (__GNUC__>4 || (__GNUC__==4 && __GNUC_MINOR__>=3))
    #define MUR_READ_UINT32(ptr)   (__builtin_bswap32(*((uint32_t*)(ptr))))
  #else
    /* Without a known fast bswap32 we're just as well off doing this */
    #define MUR_READ_UINT32(ptr)   (ptr[0]|ptr[1]<<8|ptr[2]<<16|ptr[3]<<24)
    #define MUR_UNALIGNED_SAFE
  #endif
#else
  /* Unknown endianess so last resort is to read individual bytes */
  #define MUR_READ_UINT32(ptr)   (ptr[0]|ptr[1]<<8|ptr[2]<<16|ptr[3]<<24)

  /* Since we're not doing word-reads we can skip the messing about with realignment */
  #define MUR_UNALIGNED_SAFE
#endif

/* Find best way to MUR_ROTL32 */
#if defined(_MSC_VER)
  #include <stdlib.h>  /* Microsoft put _rotl declaration in here */
  #define MUR_ROTL32(x,r)  _rotl(x,r)
#else
  /* gcc recognises this code and generates a rotate instruction for CPUs with one */
  #define MUR_ROTL32(x,r)  (((uint32_t)x << r) | ((uint32_t)x >> (32 - r)))
#endif


/*-----------------------------------------------------------------------------
 * Core murmurhash algorithm macros */

#define MUR_C1  (0xcc9e2d51)
#define MUR_C2  (0x1b873593)

/* This is the main processing body of the algorithm. It operates
 * on each full 32-bits of input. */
#define MUR_DOBLOCK(h1, k1) do{ \
        k1 *= MUR_C1; \
        k1 = MUR_ROTL32(k1,15); \
        k1 *= MUR_C2; \
        \
        h1 ^= k1; \
        h1 = MUR_ROTL32(h1,13); \
        h1 = h1*5+0xe6546b64; \
    }while(0)


/* Append unaligned bytes to carry, forcing hash churn if we have 4 bytes */
/* cnt=bytes to process, h1=name of h1 var, c=carry, n=bytes in c, ptr/len=payload */
#define MUR_DOBYTES(cnt, h1, c, n, ptr, len) do{ \
    int _i = cnt; \
    while(_i--) { \
        c = c>>8 | *ptr++<<24; \
        n++; len--; \
        if(n==4) { \
            MUR_DOBLOCK(h1, c); \
            n = 0; \
        } \
    } }while(0)

/*---------------------------------------------------------------------------*/

/* Main hashing function. Initialise carry to 0 and h1 to 0 or an initial seed
 * if wanted. Both ph1 and pcarry are required arguments. */
MUR_INLINE
void PMurHash32_Process(uint32_t *ph1, uint32_t *pcarry, const void *key, int len)
{
  uint32_t h1 = *ph1;
  uint32_t c = *pcarry;

  const uint8_t *ptr = (uint8_t*)key;
  const uint8_t *end;

  /* Extract carry count from low 2 bits of c value */
  int n = c & 3;

#if defined(MUR_UNALIGNED_SAFE)
  /* This CPU handles unaligned word access */

  /* Consume any carry bytes */
  int i = (4-n) & 3;
  if(i && i <= len) {
    MUR_DOBYTES(i, h1, c, n, ptr, len);
  }

  /* Process 32-bit chunks */
  end = ptr + len/4*4;
  for( ; ptr < end ; ptr+=4) {
    uint32_t k1 = MUR_READ_UINT32(ptr);
    MUR_DOBLOCK(h1, k1);
  }

#else /*MUR_UNALIGNED_SAFE*/
  /* This CPU does not handle unaligned word access */

  /* Consume enough so that the next data byte is word aligned */
  int i = -(long)ptr & 3;
  if(i && i <= len) {
      MUR_DOBYTES(i, h1, c, n, ptr, len);
  }

  /* We're now aligned. Process in aligned blocks. Specialise for each possible carry count */
  end = ptr + len/4*4;
  switch(n) { /* how many bytes in c */
  case 0: /* c=[----]  w=[3210]  b=[3210]=w            c'=[----] */
    for( ; ptr < end ; ptr+=4) {
      uint32_t k1 = MUR_READ_UINT32(ptr);
      MUR_DOBLOCK(h1, k1);
    }
    break;
  case 1: /* c=[0---]  w=[4321]  b=[3210]=c>>24|w<<8   c'=[4---] */
    for( ; ptr < end ; ptr+=4) {
      uint32_t k1 = c>>24;
      c = MUR_READ_UINT32(ptr);
      k1 |= c<<8;
      MUR_DOBLOCK(h1, k1);
    }
    break;
  case 2: /* c=[10--]  w=[5432]  b=[3210]=c>>16|w<<16  c'=[54--] */
    for( ; ptr < end ; ptr+=4) {
      uint32_t k1 = c>>16;
      c = MUR_READ_UINT32(ptr);
      k1 |= c<<16;
      MUR_DOBLOCK(h1, k1);
    }
    break;
  case 3: /* c=[210-]  w=[6543]  b=[3210]=c>>8|w<<24   c'=[654-] */
    for( ; ptr < end ; ptr+=4) {
      uint32_t k1 = c>>8;
      c = MUR_READ_UINT32(ptr);
      k1 |= c<<24;
      MUR_DOBLOCK(h1, k1);
    }
  }
#endif /*MUR_UNALIGNED_SAFE*/

  /* Advance over whole 32-bit chunks, possibly leaving 1..3 bytes */
  len -= len/4*4;

  /* Append any remaining bytes into carry */
  MUR_DOBYTES(len, h1, c, n, ptr, len);

  /* Copy out new running hash and carry */
  *ph1 = h1;
  *pcarry = (c & ~0xff) | n;
} 

/*---------------------------------------------------------------------------*/

/* Finalize a hash. To match the original Murmur3A the total_length must be provided */
MUR_INLINE
uint32_t PMurHash32_Result(uint32_t h, uint32_t carry, uint32_t total_length)
{
  uint32_t k1;
  int n = carry & 3;
  if(n) {
    k1 = carry >> (4-n)*8;
    k1 *= MUR_C1; k1 = MUR_ROTL32(k1,15); k1 *= MUR_C2; h ^= k1;
  }
  h ^= total_length;

  /* fmix */
  h ^= h >> 16;
  h *= 0x85ebca6b;
  h ^= h >> 13;
  h *= 0xc2b2ae35;
  h ^= h >> 16;

  return h;
}

/*---------------------------------------------------------------------------*/

/* Murmur3A compatable all-at-once */
MUR_INLINE
uint32_t PMurHash32(uint32_t seed, const void *key, int len)
{
  uint32_t h1=seed, carry=0;
  PMurHash32_Process(&h1, &carry, key, len);
  return PMurHash32_Result(h1, carry, len);
}

/*---------------------------------------------------------------------------*/

#if 0
/* Provide an API suitable for smhasher */
void PMurHash32_test(const void *key, int len, uint32_t seed, void *out)
{
  uint32_t h1=seed, carry=0;
  const uint8_t *ptr = (uint8_t*)key;
  const uint8_t *end = ptr + len;

#if 0 /* Exercise the progressive processing */
  while(ptr < end) {
    //const uint8_t *mid = ptr + rand()%(end-ptr)+1;
    const uint8_t *mid = ptr + (rand()&0xF);
    mid = mid<end?mid:end;
    PMurHash32_Process(&h1, &carry, ptr, mid-ptr);
    ptr = mid;
  }
#else
  PMurHash32_Process(&h1, &carry, ptr, (int)(end-ptr));
#endif
  h1 = PMurHash32_Result(h1, carry, len);
  *(uint32_t*)out = h1;
}
#endif

#endif
