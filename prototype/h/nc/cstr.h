#:base
#:type


#nsh_cstr(x) ((x).cstr)


inline char *char.cstr {return this;}

char *int.cstr;
char *U32.cstr;
char *F32.cstr;
char *F64.cstr;

S8 char.asS8;
U8 char.asU8;
S16 char.asS16;
U16 char.asU16;
S32 char.asS32;
U32 char.asU32;
F32 char.asF32;
F64 char.asF64;

struct CStrs *char.split(char delim);



typedef struct {
  char *dir;
  char *name;
  char *ext;
} url_t;


url_t *char.url_parts;

