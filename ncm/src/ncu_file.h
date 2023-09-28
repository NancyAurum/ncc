#ifndef NCU_FILE_H
#define NCU_FILE_H

#include <stdio.h>
#include <stdint.h>

#ifndef INCLUDE_STB_DS_H
#include "stb_ds.h"
#endif

#define FILE_SIZE_ERROR 0xFFFFFFFF
static uint32_t fileSize(char *filename) {
  FILE *fp = fopen(filename, "rb");
  if (!fp) return FILE_SIZE_ERROR;
  fseek(fp, 0L, SEEK_END);
  uint32_t sz = ftell(fp);
  fclose(fp);
  return sz;
}

static uint8_t *fileGet(uint32_t *rsize, char *filename) {
  uint32_t sz = fileSize(filename);
  if (sz == FILE_SIZE_ERROR) return 0;
  FILE *fp = fopen(filename, "rb");
  if (!fp) return 0;
  *rsize = sz;
  uint8_t *p = 0;
  arrsetlen(p, sz+1);
  p[sz] = 0;
  fread(p, 1, sz, fp);
  fclose(fp);
  return p;
}

static int fileSet(char *filename, uint8_t *data, uint32_t size) {
  FILE *fp = fopen(filename, "wb");
  if (!fp) return 0;
  fwrite(data, 1, size, fp);
  fclose(fp);
  return 1;
}

static int fileExist(char *filename) {
  FILE *fp = fopen(filename, "rb");
  if (!fp) return 0;
  fclose(fp);
  return 1;
}

static char *execCommand(char *cmd) {
  char *r;
  int rdsz = 1024;
  int len = rdsz;
  int pos = 0;
  int s;
  FILE *in = popen(cmd, "r");

  if (!in) return 0;

  r = (char*)malloc(len);

  for (;;) {
    if (pos + rdsz > len) {
      char *t = r;
      len = len*2;
      r = (char*)malloc(len);
      memcpy(r, t, pos);
      free(t);
    }
    s = fread(r+pos,1,rdsz,in);
    pos += s;
    if (s != rdsz) break;
  }

  pclose(in);

  r[pos] = 0;
  if (pos && r[pos-1] == '\n') r[pos-1] = 0;

  return r;
}

#endif
