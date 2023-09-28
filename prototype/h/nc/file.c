#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#:file.h

//class !FILE; //no need, since it predefined by NCC

void CFile.ctor_i {
  m_opaque = 0;
}

void CFile.dtor_i {
  this.close;
}

#FILE_LINE_SIZE 1024

static char file_line[FILE_LINE_SIZE];

//FIXME: file_line buffer should be resizeable and thread safe
char *CFile.line {
  if (!fgets(file_line, FILE_LINE_SIZE, (FILE*)(m_opaque))) return 0;
  file_line[strlen(file_line)-1] = 0; //remove new line
  return file_line;
}

int CFile.ropen(char *filename) {
  if (m_opaque) this.close;
  m_opaque = fopen(filename, "rb");
  return m_opaque != 0;
}

int CFile.copen(char *filename) {
  if (m_opaque) this.close;
  m_opaque = fopen(filename, "wb");
  return m_opaque != 0;
}

void CFile.close {
  if (!m_opaque) return; //should it be assert != 0?
  fclose((FILE*)(m_opaque));
  m_opaque = 0;
}

CFile *CFile.write(void *bytes, int len) {
  fwrite(bytes, 1, len, (FILE*)(m_opaque));
  return this;
}

int CFile.read(void *bytes, int len) {
  return fread(bytes, 1, len, (FILE*)(m_opaque));
}

#CFile_readXs(type) {
type CFile.read#<type>(int len) {
  type xs;
  xs.init(len);
  this.read(xs.elts, len*sizeof(xs.elts[0]));
  return xs;
}
}

CFile_readXs(U8s)
CFile_readXs(U16s)
CFile_readXs(U32s)
CFile_readXs(S8s)
CFile_readXs(S16s)
CFile_readXs(S32s)

#if 0
U8s CFile.readU8s(int len) {
  U8s xs;
  xs.init(len);
  this.read(xs.elts, len);
  return xs;
}
#endif

CFile *CFile.writeSrlz(CFileSrlzBuf sr) {
  if (sr.len < 0) {
    fwrite(sr.local, 1, -sr.len, (FILE*)(m_opaque));
  } else {
    fwrite(sr.bytes, 1, sr.len, (FILE*)(m_opaque));
    free(sr.bytes);
  }
  return this;
}

void char.serialize(CFile &out) {
  U32 len = strlen(this);
  out.write(&len, 4);
  out.write(this, len);
}


char *CFile.dsrlz_cstr {
  U32 len;
  this.read(&len, 4);
  char *s = (char*)malloc(len+1);
  this.read(s, len);
  s[len] = 0;
  return s;
}


#if #NCC_WINAPI
#ftello _ftelli64
#fseeko _fseeki64
#endif

CFile *CFile.seek(U64 offset) {
  if (fseeko(m_opaque, offset, SEEK_SET)) //fseeko returns 0 on success
    return 0;
  return this;
}

U64 CFile.tell {
  return ftello(m_opaque);
}

U64 CFile.size {
  U64 pos = this.tell;
  if (fseeko(m_opaque, 0, SEEK_END)) //fseeko returns 0 on success
    return 0;
  U64 sz = ftello(m_opaque);
  fseeko(m_opaque, pos, SEEK_SET);
  return sz;
}
