#:mem
#:tlst
#:cstr
#:vec3


char *int.cstr {
  int n = *this;
  int l = snprintf(NULL, 0, "%d", n);
  char *s = (char*)mAlloc(l+1);
  sprintf(s, "%d", n);
  return s;
}

char *U32.cstr {
  int n = *this;
  int l = snprintf(NULL, 0, "0x%x", n);
  char *s = (char*)mAlloc(l+1);
  sprintf(s, "0x%x", n);
  return s;
}

char *F32.cstr {
  F32 n = *this;
  int l = snprintf(NULL, 0, "%g", n);
  char *s = (char*)mAlloc(l+1);
  sprintf(s, "%g", n);
  return s;
}

char *F64.cstr {
  F64 n = *this;
  int l = snprintf(NULL, 0, "%g", n);
  char *s = (char*)mAlloc(l+1);
  sprintf(s, "%g", n);
  return s;
}

char *vec3.cstr {
  vec3 v = *this;
  int l = snprintf(NULL, 0, "(%g,%g,%g)", v.x,v.y,v.z);
  char *s = (char*)mAlloc(l+1);
  sprintf(s, "(%g,%g,%g)", v.x,v.y,v.z);
  return s;
}

S8 char.asS8 {return atoi(this);}
U8 char.asU8 {return atoi(this);}
S16 char.asS16 {return atoi(this);}
U16 char.asU16 {return atoi(this);}
S32 char.asS32 {return atoi(this);}
U32 char.asU32 {return atoi(this);} //FIXME: handle the full range
F32 char.asF32 {return atof(this);}
F64 char.asF64 {return atof(this);}


CStrs *char.split(char delim) {
  auto r = new(CStrs);
  auto d = this.dup; //in case it resides in ROM
  auto q = d;
  do {
    auto p = q;
    while (*q && *q != delim) q++;
    if (!*q) {
      r.push(p.dup);
      break;
    }
    *q = 0;
    r.push(p.dup);
  } while(*++q);
  delete(d);
  return r;
}

url_t *char.url_parts {
  char *path = this;

  int bufsz = strlen(path)+3;
  url_t *fn = malloc(sizeof(url_t)+bufsz);
  char *r = (char*)(fn+1);
  char *dir;
  char *name;
  char *ext;
  char *p, *q;
  int l;

  if ((p = strrchr(path, '/'))) {
    l = p-path + 1;
    dir = r;
    strncpy(dir, path, l);
    dir[l] = 0;
    p++;
    r += l+1;
  } else {
    p = path;
    dir = r;
    *r++ = 0;
  }
  if ((q = strrchr(p, '.'))) {
    l = q-p;
    name = r;
    strncpy(name, p, l);
    name[l] = 0;
    q++;
    r += l+1;

    ext = r;
    l = strlen(q);
    strcpy(ext, q);
  } else {
    ext = r;
    *r++ = 0;
    name = r;
    strcpy(name, p);
  }

  fn->dir = dir;
  fn->name = name;
  fn->ext = ext;

  return fn;
}
