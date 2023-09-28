#:base

class CFile {
  void *m_opaque;
}

void CFile.ctor_i;
void CFile.dtor_i;


CTOR(CFile) {this.ctor_i;}
DTOR(CFile) {this.dtor_i;}


char *CFile.line;

//opens existing file for reading
int CFile.ropen(char *filename);

//creates a new file, or trunactes existing file zero length
int CFile.copen(char *filename);

U64 CFile.tell;
CFile *CFile.seek(U64 offset); //File.seek(off).readS32s(count)
U64 CFile.size;


//explicitly closes the file.
//called automatically by DTOR.
void CFile.close;

CFile *CFile.write(void *bytes, int len);
int CFile.read(void *bytes, int len);

#CFile_readType(type) {
inline type CFile.read#<type>() {
  type t;
  this.read(&t,sizeof(t));
  return t;
}}

CFile_readType(S8)
CFile_readType(U8)
CFile_readType(S16)
CFile_readType(U16)
CFile_readType(S32)
CFile_readType(U32)
CFile_readType(S64)
CFile_readType(U64)
CFile_readType(F32)
CFile_readType(F64)

typedef struct {
  int len;
  union {
    U8 *bytes;
    U8 local[8];
  };
} CFileSrlzBuf;

CFile *CFile.writeSrlz(CFileSrlzBuf sr);

#srlz(out) serialize(&(out))

#srlz_int(type) {
inline void type.serialize(CFile &out) {
  out.write(this, sizeof(*this));
}
}

srlz_int(S8)
srlz_int(U8)
srlz_int(S16)
srlz_int(U16)
srlz_int(S32)
srlz_int(U32)
srlz_int(S64)
srlz_int(U64)

void char.serialize(CFile &out);


#dsrlz_int(type) {
inline int type.deserialize(CFile &in) {
  return in.read(this, sizeof(*this));
}
}

#dsrlz(in) deserialize(&(in))

dsrlz_int(S8)
dsrlz_int(U8)
dsrlz_int(S16)
dsrlz_int(U16)
dsrlz_int(S32)
dsrlz_int(U32)
dsrlz_int(S64)
dsrlz_int(U64)

char *CFile.dsrlz_cstr;
