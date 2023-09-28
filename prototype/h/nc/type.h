#include <string.h>

#:base

inline int int.eq(int v) {return *this == v;}
inline int int.ne(int v) {return *this != v;}

inline int char.eq(char *s) {return !strcmp(this,s);}
inline int char.ne(char *s) {return strcmp(this,s);}

//ignore-case eq
inline int char.eqi(char *s) {return !strcasecmp(this,s);}
inline int char.nei(char *s) {return strcasecmp(this,s);}



inline int char.begins(char *kw) {
  return !strncmp(this, kw, strlen(kw));
}


inline char *char.dtor {return this;}
