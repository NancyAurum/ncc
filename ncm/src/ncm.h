/*
              IMPLEMENTATION OF
        THE NEW C MACRO LANGUAGE (NCM)
   by 2023 Nancy Sadkov <nangld85@gmail.com>.
*/


/*
To use, include this file into one of your .c files like that:
  #define NCM_IMPLEMENTATION
  #include "ncm.h"

Then use the ncm_ prefixed functions below.
*/

#ifndef NCM_H
#define NCM_H

#include <stdint.h>

#define NCM_NO_LINE_NUMS    0x001
#define NCM_KEEP_COMMENTS   0x002
#define NCM_NO_LINE_MACRO   0x004
#define NCM_PARENLESS_ARGS  0x008

typedef struct {
  //ARGUMENTS
  char **paths;
  uint32_t flags;
  void *user; //user provided handle
              //available to callbacks through ncm_user
  
  char mchar; // Macro character. By default #

  //CALLBACKS provided by user
  
  //called when a fatal error has occured
  void (*err_fatal)(void *ncm, char *macro
                   ,char *file, int row, int col, char *description);

  //checks is a file exists (using in include)
  int (*file_exist)(void *ncm, char *filename);

  //reads entires file, storing its size at the *size pointer
  uint8_t *(*file_get)(void *ncm, uint32_t *size, char *filename);

  //if non zero, will be called to process $(...) commands
  //returns command result, which will be macroexpanded further
  char *(*command)(void *ncm, char *);
} ncm_options_t;


// preinits options structure for ncm_expand_file and ncm_eval
ncm_options_t ncm_default_options();

// macroexpands a file, using file_exist and file_get to obtain the data
char *ncm_expand_file(ncm_options_t *opt, char *filename);

// evaluates expr, with `name` being used to report errors with err_fatal
char *ncm_eval(ncm_options_t *opt, char *name, char *expr);

// free result returned by ncm_expand_file
void ncm_free_result(char *result);

// extracts ncm_options_t.user from ncm_state
void *ncm_user(void *ncm_state);



#ifdef NCM_IMPLEMENTATION
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>
#include "stb_ds.h"


#define arrdup(xs) ((xs) ? \
     (void*)((uint8_t*)memcpy(malloc(sizeof(*stbds_header(xs)) \
                   + stbds_header(xs)->capacity*sizeof(xs[0])) \
           , stbds_header(xs) \
           ,(sizeof(*stbds_header(xs)) \
              + stbds_header(xs)->capacity*sizeof(xs[0])) \
           )+sizeof(*stbds_header(xs))) \
    : 0)


#define alen(a)   arrlen(a)
#define aput(a,v) arrput(a,v)
#define apop(a)   arrpop(a)
#define alast(a)  arrlast(a)
#define adup(a)   arrdup(a)


#define U8  uint8_t
#define U16 uint16_t
#define U32 uint32_t
#define S8  int8_t
#define S16 int16_t
#define S32 int
#define F32 float
#define F64 double
#define U64 uint64_t
#define S64 int64_t


static char *_hidden_cat_(char *a0, ...) {
  char *a;
  va_list ap;
  int size = strlen(a0);
  va_start(ap, a0);
  for (;;) {
    a = va_arg(ap, char*);
    if (!a) break;
    size += strlen(a);
  }
  va_end(ap);
  size += 1;

  char *o = malloc(size);

  char *p = o;

  a = a0;
  while (*a) *p++ = *a++;

  va_start(ap, a0);
  for (;;) {
    a = va_arg(ap, char*);
    if (!a) break;
    while (*a) *p++ = *a++;
  }
  va_end(ap);

  *p++ = 0;

  return o;
}

#define cat(...) _hidden_cat_(__VA_ARGS__, 0)

typedef struct {
  char *dir;
  char *name;
  char *ext;
} url_t;

static url_t *url_parts(char *path) {
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

///////////////////////////////////////////////////////////////////
//////////////////// ACTUAL NCM CODE //////////////////////////////

#define NCM_INCLUDE_DEPTH_LIMIT 4096
#define NCM_MACRO_DEPTH_LIMIT  8192


//rfile_t.flags
#define F_BUFFER  0x001
#define F_BASE    0x002
#define F_PRIVATE 0x004


//RAM cached file
typedef struct {
  U8 *data;
  U32 size;
  char *name;
  url_t *url;
  int included; //counts how many times this file was already included
  U32 flags;
} rfile_t;

struct filep_t;
typedef struct filep_t filep_t;

struct filep_t {
  U8 *start;
  U8 *ptr;
  U8 *end;
  rfile_t *file;
  U32 col; //column counter
  U32 pcol; // prev column count
  U32 row; //line counter
  filep_t *prev;
};


#define M_NO_BODY -1

#define M_ONE_LINE 0x001

#define M_NOREC 0x002


typedef struct {
  char *name;
  int nargs;
  char **args;
  char **ds; //default values;
  char *body;
  int row;
  int col;
  char *filename;
  int bodyarg; //number of the {} body arg or M_NO_BODY if there is none
  int variadic; //index of the variadic arg
  int optarg; // start of the optional arguments
  int flags;
  int depth; //recursive call depth
} macro_t;

typedef struct { char *key; char *value; } *args_table_t;

typedef struct { U32 row; U32 col; char *ptr; } abody_t;


typedef struct { char *key; macro_t *value; } *macro_tbl_t;

typedef struct {
  filep_t *filep; //cur file

  ncm_options_t opt;

  //macro table
  macro_tbl_t mt;

  //currently active macros list
  macro_t **ml;

  //file table
  struct { char *key; rfile_t *value; } *ft;

  macro_tbl_t *scopes;

  U8 *out; //output buffer
  int row; //output row
  int col; //output col

  U32 scope_col; //column counter
  U32 scope_row; //line counter

  abody_t abody;

  U32 mex_count; //number of times macroexpand() got called.

  char **paths; //include directories

  //cmacros  
  struct { char *key; char *value; } *cmacros;
  
  args_table_t at;
  
  U32 position_count; //count the number of times emit_position() got called
  
  int include_depth;

} ncm_state;

#define filep this->filep
#define MCH (this->opt.mchar)

//FIXME: when fatal error happens, the ncm_state should be freed
static void fatalF(ncm_state *this, char *fmt, ...) {
  char *filename = 0;
  char *macroname = 0;
  int row = 0;
  int col = 0;
  for (filep_t *fp = filep; fp; fp = fp->prev) {
    if (!(fp->file->flags & F_BASE)) {
      if (!macroname) macroname = fp->file->name;
    } else {
      if (!filename) {
        filename = fp->file->name;
        row = fp->row;
        col = fp->col;
      }
    }
  }
  if (this->opt.err_fatal) {
    va_list ap;
    va_start(ap, fmt);
    int l = vsnprintf(NULL, 0, fmt, ap);
    va_end(ap);
    char *s = (char*)malloc(l+1);

    va_start(ap, fmt);
    vsprintf(s, fmt, ap);
    va_end(ap);
    this->opt.err_fatal(this, macroname, filename, row, col, s);
  }
  exit(-1);
}

#define fatal(...) fatalF(this, __VA_ARGS__)

static int isquote(int c) {
  return c == '\"' || c == '\'' || c == '`';
}

static int issymchr(int c) {
  return isalnum(c) || c == '_';
}

static int isopchrF(ncm_state *this, int c) {
  return c && !issymchr(c) && !isspace(c)
         && c != MCH && c != '\\'
         && c != '\"' && c != '\''
         //uncomment if your language uses ` as string operator
         //&& c != '\`'
         && c != '(' && c != ')'
         && c != '{' && c != '}'
         && c != '>';
}

#define isopchr(c) isopchrF(this, c)

static U8 pop_charF(ncm_state *this) {
  if (filep->ptr == filep->end) return 0;
  U8 ch = *filep->ptr++;
  if (ch == '\n') {
    filep->row++;
    filep->pcol = filep->col;
    filep->col = 0;
  } else {
    ++filep->col;
  }
  return ch;
}

#define pop_char() pop_charF(this)

static U8 unpop_charF(ncm_state *this) {
  int ch = *--filep->ptr;
  if (ch == '\n') {
    filep->row--;
    filep->col = filep->pcol;
    filep->pcol = -1;
  }
  return ch;
}

static U8 next_charF(ncm_state *this) {
  if (filep->ptr == filep->end) return 0;
  return *filep->ptr;
}

static void put_charF(ncm_state *this, U8 ch) {
  if (ch != '\n') this->col++;
  else {
    this->col = 0;
    this->row++;
  }
  aput(this->out, ch);
}

#define put_char(ch) put_charF(this,ch)

static void put_cstr(ncm_state *this, char *s) {
  for ( ; *s; s++) put_char(*s);
}


static void expect_charF(ncm_state *this, int ch) {
  int c = pop_char();
  if (c != ch) {
    if (c) fatal("expected `%c` (got `%c`)", ch, c);
    else fatal("expected `%c` (got EOF)", ch);
  }
}

#define unpop_char() unpop_charF(this)
#define next_char() next_charF(this)
#define expect_char(ch) expect_charF(this,ch)


static void skip_count(ncm_state *this, int n) {
  while(n-- > 0) pop_char();
}

#define aput_count(a,n) for(int k = 0; k < n; k++) aput(a,pop_char())

//#define aputa(a,b) for(int k = 0; k < alen(b); k++) aput(a,b[k])

#define aputs(a,b) for(char *p_ = b; *p_; p_++) aput(a,*p_)


static filep_t *cur_filep(ncm_state *this) {
  filep_t *p = filep;
  if (!p) return 0;

  while (p && p->file->flags&F_BUFFER) p = p->prev;
  return p;
}

static filep_t *cur_scope(ncm_state *this) {
  filep_t *p = filep;
  if (!p) return 0;
  while (!(p->file->flags&F_BASE)) p = p->prev;
  return p;
}


static char *fmt(char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  int l = vsnprintf(NULL, 0, fmt, ap);
  va_end(ap);
  char *s = NULL;
  arrsetlen(s, l+1);
  va_start(ap, fmt);
  vsprintf(s, fmt, ap);
  va_end(ap);
  return s;
}

static void put_fmt(ncm_state *this, char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  int l = vsnprintf(NULL, 0, fmt, ap);
  va_end(ap);
  char *s = (char*)malloc(l+1);

  va_start(ap, fmt);
  vsprintf(s, fmt, ap);
  va_end(ap);
  put_cstr(this, s);
  free(s);
}



static char *get_sym(ncm_state *this) {
  char *r = NULL;
  while (issymchr(next_char())) aput(r, pop_char());
  aput(r,0);
  return r;
}

static char *get_dec(ncm_state *this) {
  char *r = NULL;
  while (isdigit(next_char())) aput(r, pop_char());
  aput(r,0);
  return r;
}

static char *get_hex(ncm_state *this) {
  char *r = NULL;
  while (isxdigit(next_char())) aput(r, pop_char());
  aput(r,0);
  return r;
}


static char *get_op(ncm_state *this) {
  char *r = NULL;
  while (isopchr(next_char())) aput(r, pop_char());
  aput(r,0);
  return r;
}

static char *get_line(ncm_state *this) {
  char *r = NULL;
  while (next_char() && next_char() != '\n') aput(r, pop_char());
  aput(r,0);
  return r;
}

static char *get_comment(ncm_state *this);

#define SKIPWS_BASIC  0x000
#define SKIPWS_COPY   0x001
#define SKIPWS_NO_NL  0x002
#define SKIPWS_ESC_NL 0x003

static void skipws(ncm_state *this, int type) {
again:
  while (isspace(next_char())) {
    if ((type&SKIPWS_NO_NL) && next_char()=='\n') break;
    int ch = pop_char();
    if (type&SKIPWS_COPY) put_char(ch);
  }
  
  int ch = next_char();
  if (type == SKIPWS_ESC_NL && ch == '\\') {
    pop_char();
    int ch2 = next_char();
    if (ch2 == '\n') {
      pop_char();
      goto again;
    }
    unpop_char();
  }
  if (ch == '/') {
    int ch = pop_char();
    if (next_char() == '/' || next_char() == '*') {
      unpop_char();
      char *cmt = get_comment(this);
      if (type&SKIPWS_COPY) put_cstr(this, cmt);
      arrfree(cmt);
      goto again;
    } else {
      unpop_char();
    }
  }
}

static char *get_body_comment(ncm_state *this, char *r) {
  char *cmt = get_comment(this);
  aputs(r,cmt);
  arrfree(cmt);
  return r;
}

static char *get_body_string(ncm_state *this, int term, char *r) {
  aput(r,pop_char());
  for (;;) {
    int ch = pop_char();
    aput(r,ch);
    if (ch == '\\') {
      aput(r,pop_char());
    } else if (ch == term) {
      break;
    } else if (!ch) {
      break;
    }
  }
  return r;
}

//FIXME: embedded macros, comments and strings
static char *get_body(ncm_state *this, int *flags) {
  int term = '\n';
  if (next_char() == '{') {
    term = '}';
    pop_char();
  } else {
    if (flags) *flags |= M_ONE_LINE;
  }
  char *r = NULL;
  int depth = 0;
  for (;;) {
    int ch = next_char();
    if (term == '}' && ch == '{') {
      aput(r,pop_char());
      depth++;
    } else if (term == '\n' && ch == '(') {
      aput(r,pop_char());
      depth++;
    } else if (term == '\n' && ch == ')') {
      if (!depth) break;
      aput(r,pop_char());
      depth--;
    } else if (ch == term) {
      if (!depth) {
        if (term != '\n') pop_char();
        break;
      }
      aput(r, pop_char());
      depth--;
    } else if (!ch) {
      break;
    } else if (ch == '\"' || ch == '\'') {
      r = get_body_string(this, ch, r);
    } else if (ch == '/') {
      if (filep->ptr[1]=='/' || filep->ptr[1]=='*') {
        r = get_body_comment(this, r);
      } else {
        aput(r,pop_char());
      }
    } else if (ch == '\\') {
      aput(r,pop_char());
      aput(r,pop_char());
    } else {
      aput(r,pop_char());
    }
  }
  aput(r,0);
  return r;
}


//FIXME move common parts of get_body and get_cond_body
static char *get_cond_body(ncm_state *this) {
  char *r = NULL;
  int depth = 0;
  for (;;) {
    int ch = next_char();
    if (ch == MCH) {
      if (!strncmp((char*)filep->ptr+1,"if", 2)) {
        depth++;
        aput(r,pop_char());
        aput_count(r,2);
        continue;
      } else if (!strncmp((char*)filep->ptr+1,"elif", 4)) {
        if (!depth) break;
        aput(r,pop_char());
        aput_count(r,4);
        continue;
      } else if (!strncmp((char*)filep->ptr+1,"else", 4)) {
        if (!depth) break;
        aput(r,pop_char());
        aput_count(r,4);
        continue;
      } else if (!strncmp((char*)filep->ptr+1,"endif", 5)) {
        if (!depth) {
          skipws(this,SKIPWS_NO_NL);
          if (next_char() == '\n') pop_char();
          break;
        }
        aput(r,pop_char());
        aput_count(r,5);
        --depth;
        continue;
      } else {
        aput(r,pop_char());
        continue;
      }
    } else if (ch == '\'' || ch == '\"') {
      r = get_body_string(this, ch, r);
    } else if (!ch) {
      break;
    } else if (ch == '/' && (filep->ptr[1]=='/' || filep->ptr[1]=='*')) {
      r = get_body_comment(this, r);
    } else {
      aput(r,pop_char());
    }
  }
  aput(r,0);
  return r;
}


static char **parse_args(char *args, int skipws) {
  char **as = NULL;
  char *a = NULL;
  char *p = args;
  int depth = 0; //to handle '(' and ')' inside the arglist
  while (*p) {
    if (depth == 0) {
      if (*p == ',') {
        if (a) {
          aput(a, 0);
          aput(as, a);
        }
        a = NULL;
      } else if (*p == '\\' && (p[1] == '\\' || p[1] == ',' || p[1] == '(')) {
        p++;
        aput(a, *p);
      } else if (skipws && isspace(*p)) {
      } else if (*p == '(') {
        depth++;
        aput(a, *p);
      } else {
        aput(a, *p);
      }
    } else {
      if (*p == ')') {
        depth--;
      } else if (*p == '\\' && (p[1] == '\\' || p[1] == ')')) {
        p++;
      }
      aput(a, *p);
    }
    p++;
  }
  if (a) {
    aput(a, 0);
    aput(as, a);
  }
  return as;
}

static void parse_defmacro_args(ncm_state *this, macro_t *m, char *args) {
  char **as = parse_args(args, 1);
  int nargs = 0;
  for (int i = 0; i < alen(as); i++) {
    char *a = as[i];
    //printf("arg%d: `%s`\n", i, a);
    char *e = strchr(a, '=');
    if (!e && m->optarg != -1) {
      fatal("argument is missing default value: %s", a);
    }
    if (e) {
      if (m->optarg == -1) m->optarg = i;
      char *n = NULL;
      char *d = NULL;
      for (; a < e; a++) aput(n, *a);
      aput(n, 0);
      a++;
      for (; *a; a++) aput(d, *a);
      aput(d, 0);
      aput(m->ds, d);
      arrfree(as[i]);
      as[i] = n;
      nargs++;
    } else if (*a == '[') {
      m->variadic = i;
      char *p = NULL;
      a++;
      for (; *a && *a != ']'; a++) aput(p, *a);
      arrfree(as[i]);
      aput(p, 0);
      as[i] = p;
    } else if (*a == '{') {
      m->bodyarg = i;
      char *p = NULL;
      a++;
      for (; *a && *a != '}'; a++) aput(p, *a);
      arrfree(as[i]);
      aput(p, 0);
      as[i] = p;
    } else {
      nargs++;
    }
  }
  m->args = as;
  m->nargs = nargs;
}

static macro_t *add_macro(ncm_state *this, char *name, char *args
                         , char *body, int row, int col, char *filename) {
  macro_t *m = malloc(sizeof(macro_t));
  m->name = name;
  m->body = body;
  m->col = col;
  m->row = row;
  //m->file = file;
  m->filename = strdup(filename);
  m->bodyarg = M_NO_BODY;
  m->variadic = -1;
  m->nargs = -1;
  m->optarg = -1;
  m->args = 0;
  m->depth = 0;
  m->ds = 0;
  m->flags = 0;
  if (args) parse_defmacro_args(this, m, args);
  aput(this->ml, m);
  shput(this->mt, m->name, m);

  int nargs = 0;
  return m;
}

static char *read_parens(ncm_state *this, int o, int c, int e) {
  char *r = NULL;
  pop_char();
  int depth = 0;
  for (;;) {
    int ch = pop_char();
    aput(r,ch);
    if (ch == e) {
      if (next_char() == e || next_char() == o || next_char() == c) {
        apop(r);
        aput(r,pop_char());
      }
    } else if (ch == c) {
      if (!depth) {
        apop(r);
        break;
      }
      depth--;
    } else if (ch == o) {
      depth++;
    } else if (!ch) {
      break;
    }
  }
  aput(r,0);
  return r;
}


static void emit_position(ncm_state *this);
static void expand_file2(ncm_state *this, char *filename);
static void open_buffer(ncm_state *this, char *name, U8 *content, U32 size);
static void close_buffer(ncm_state *this);

static void process_file(ncm_state *this);

#define INJECT_IMPLICIT 0x01
#define INJECT_LOCAL    0x02

#define save_position() \
  U32 saved_row = filep->row; \
  U32 saved_col = filep->col; \
  U32 saved_pcol = filep->pcol; \
  U8 *saved_ptr = filep->ptr;


#define load_position() \
  filep->row = saved_row; \
  filep->col = saved_col; \
  filep->pcol = saved_pcol; \
  filep->ptr = saved_ptr;



#define ME_BASE_SCOPE   0x001
#define ME_MACRO_SCOPE  0x002
#define ME_NO_POSITION  0x004
#define ME_STANDALONE   0x008


static S32 eval_expr(ncm_state *this);
static char *macroexpand(ncm_state *this, macro_t *m
                         , char *args, int flags);
static char *macroexpand2(ncm_state *this, char *name, char *body, U32 flags);

static char *inject_vars(ncm_state *this, char *mname, char *body
                        ,args_table_t at, int flags) {
  char *r = NULL;
  char *b = body;
  int implicit = flags&INJECT_IMPLICIT;
  int only_local = flags&INJECT_LOCAL;
  args_table_t sat = this->at;
  if (at) this->at = at;
  while (*b) {
    int c = *b;
    if (c == MCH) {
      if (b[1] == '[') {
        b += 2;
        save_position();
        filep->ptr = (U8*)b; //FIXME: huge kludge
        S32 result = eval_expr(this);
        b = (char*)filep->ptr;
        load_position();
        if (*b  != ']') {
          fatal("unexpected `%c` (expected `]`), inside %s", *b, mname);
        }
        b++;
        char *s = fmt("%d", result);
        aputs(r, s);
        arrfree(s);        
        continue;
      }
      if (b[1] != '<') goto normal;
      b += 2;
symbol:;
      char *s = NULL;
      for (; issymchr(*b); b++) {
        aput(s, *b);
      }
      aput(s,0);

      char *v = 0;
      if (at) v = shget(at,s);
      macro_t *m = 0;
      if (!v && c==MCH) {
        m = shget(this->mt,s);
        if (m) v = m->body; //FIXME implement local macro expansion
      }

      if (c == MCH) while (isspace(*b)) b++;
      if (c == MCH && *b == '=') {
        b++;
        char *v = NULL;
        for (; *b && *b != '>'; b++) {
          aput(v, *b);
        }
        if (*b == '>') b++;
        aput(v,0);
        filep->row = filep->row;
        filep->col = filep->col;
        v = macroexpand2(this, filep->file->name, v
                   , ME_STANDALONE|ME_NO_POSITION|ME_BASE_SCOPE);
        macro_t *m = shget(this->mt, s);
        if (!m) {
          add_macro(this, s, 0, v, filep->row, filep->col, filep->file->name);
        } else {
          arrfree(m->body);
          m->body = v;
          arrfree(s);
        }
        continue;
      }
      char *tmp = 0;
      if (!v) {
        //undo
        if (c == MCH) {
          aput(r,MCH);
          aput(r,'<');
        }
        v = s;
      } else if (c == MCH) {
        while(isspace(*b)) b++;
        if (m && m->nargs != -1 && *b == '(') {
          save_position();
          filep->ptr = (U8*)b; //FIXME: huge kludge
          char *args = NULL;
          if (m->nargs != -1) {
            if (next_char() != '(') {
              fatal("no argument list for macro `%s`", m->name);
            }
            args = read_parens(this, '(', ')', '\\');
          }
          b = (char*)filep->ptr;
          load_position();
          char *abody = NULL;
          abody_t sabody = this->abody;
          this->abody.ptr = abody;
          v = macroexpand(this, m, args, ME_STANDALONE);
          this->abody = sabody;
          if (args) arrfree(args);
          if (abody) arrfree(abody);
          tmp = v;
        }
        if (*b == '>') b++;
      }
      if (v == this->abody.ptr) {
        if (this->opt.flags&NCM_NO_LINE_NUMS) {
        } else {
          char *s = fmt("#line %d \"%s\"\n"
                       ,this->abody.row+1
                       ,filep->file->name);
          if (!alen(r) || alast(r) != '\n') aput(r, '\n');
          aputs(r,s);
          arrfree(s);
        }
      }
      for (; *v; v++) aput(r,*v);
      arrfree(s);
      if (tmp) arrfree(tmp);

      continue;
    }
normal:
    if (implicit && issymchr(c)) {
      goto symbol;
    }
    if (isquote(*b)) {
      int term = *b++;
      aput(r,term);
      for (; *b; b++) {
        if (*b == '\\') {
          b++;
          aput(r,*b);
          if (*b != MCH) aput(r,*b); //special case of user escaping expand
        } else if (*b == MCH) {
          b++;
          int o = *b;
          if (o == '<' || issymchr(o)) {
            if (o == '<') b++;
            char *s = NULL;
            for (; issymchr(*b); b++) {
              aput(s, *b);
            }
            aput(s,0);
            b--;
            if (o == '<' && *b == '>') b++;
            char *v = shget(at,s);
            if (!v) v = s;
            for (; *v; v++) aput(r,*v);
            arrfree(s);
          } else {
            fatal("unexpected `#%c` while expanding `%s`", *b, mname);
          }
        } else if (*b == term) {
          aput(r,*b);
          b++;
          break;
        } else {
          aput(r,*b);
        }
      }
    } else {
      aput(r,*b);
      b++;
    }
  }
  aput(r,0);
  this->at = sat;
    return r;
}

static char *macroexpand2(ncm_state *this, char *name, char *body, U32 flags) {
  U8 *sout = this->out;
  U32 prev_mex_count;
  int step = 0;
  int nlines = 0;
  for (char *p = body ; *p; p++) if (*p == '\n') nlines++;
  if (!nlines) flags |= ME_NO_POSITION;
  int posc = this->position_count;
  do {
    prev_mex_count = this->mex_count;
    this->out = NULL;
    open_buffer(this, name, (U8*)body, arrlen(body));

    if (flags&ME_BASE_SCOPE) {
      filep->file->flags |= F_BASE;
      filep->row = this->scope_row;
      filep->col = this->scope_col;
    } else if (flags&ME_MACRO_SCOPE) {
      filep->row = this->scope_row;
      filep->col = this->scope_col;
    }
    if (step==0 && !(flags&ME_NO_POSITION)) emit_position(this);
    process_file(this);
    close_buffer(this);
    aput(this->out, 0);
    body = (char*)this->out;
    step++;
  } while (this->mex_count != prev_mex_count);
  if (flags&ME_STANDALONE) {
    U8 *p = this->out;
    this->out = sout;
    return (char*)p;
  }
  for (U8 *p = this->out; *p; p++) aput(sout,*p);
  arrfree(this->out);
  this->out = sout;
  if (!(flags&ME_NO_POSITION) || this->position_count != posc) {
    emit_position(this);
  }
  return 0;
}

static char *macroexpand_fn(ncm_state *this, macro_t *m, char *args) {
  char *b = m->body;

  char **as = NULL;
  if (args) {
    char *args2 = inject_vars(this, m->name, args, this->at, INJECT_IMPLICIT);
    as = parse_args(args2, 0);
    arrfree(args2);
  }

  struct {char *key; char *value;} *vt = NULL;
  char **bs = NULL;
  for (int i = 0; i < alen(as); i++) {
    char *a = as[i];

    if (m->optarg == -1) {
no_setarg:
      aput(bs, a);
      as[i] = 0;
      continue;
    }
    char *e = strchr(a, '=');
    if (!e) goto no_setarg;

    char *p = a;
    while (isspace(*p)) p++;
    if (*p == '=') goto no_setarg;
    if (isopchr(e[-1])) goto no_setarg; //FIXME: handle escaped '\=' char
    int c = e[1];
    if (e[1] == '=') goto no_setarg; //==
    if (e[1] == '>') goto no_setarg; //=>

    char *n = NULL;
    char *d = NULL;
    for (; a < e; a++) aput(n, *a);
    aput(n, 0);
    a++;
    for (; *a; a++) aput(d, *a);
    aput(d, 0);
    shput(vt, n, d);
    arrfree(as[i]);
    as[i] = n;
  }
  char **tmp = bs;
  bs = as;
  as = tmp;

  int nargs = m->nargs;
  if (m->optarg != -1) nargs = m->optarg;
  if (alen(as) < nargs) {
    fatal("Not enough arguments to macro `%s`", m->name);
  } else if (alen(as) > m->nargs && m->variadic == -1) {
    fatal("Too many arguments to macro `%s`", m->name);
  }
  args_table_t at = NULL;
  int j = 0;
  char **mas = m->args;
  char *xs_n = NULL;
  char *xs_nv = NULL;

  for (int i = 0; i < alen(mas); i++) {
    char *a = mas[i];
    char *v = NULL;
    if (i == m->variadic) {
      int l = alen(as)-alen(mas) + 1;
      xs_n = fmt("%s_n", a);
      xs_nv = fmt("%d", l);
      shput(at, xs_n, xs_nv);
      for (int k = 0; k < l; k++) {
        if (k) aput(v,',');
        char *p = as[j];
        for (; *p; p++) {
          aput(v,*p);
        }
        arrfree(as[j]);
        as[j] = 0;
        j++;
      }
      aput(v, 0);
      as[j-1] = v;
    } else if (i == m->bodyarg) {
      v = this->abody.ptr;
      if (!v) v = ""; //should never happen
    } else if (m->optarg != -1 && i >= m->optarg) {
      if (j < alen(as)) {
        v = as[j++];
      } else {
        v = shget(vt,a);
        if (!v) v = m->ds[i-m->optarg];
      }
    } else {
      v = as[j++];
    }
    shput(at, a, v);
    //printf("arg%d: %s=%s\n", i, a, v);
  }
  int flags = INJECT_IMPLICIT; ///|INJECT_LOCAL;
  char *r = inject_vars(this, m->name, b, at, flags);
  shfree(at);
  
  if (xs_n) {
    arrfree(xs_n);
    arrfree(xs_nv);
  }

  for (int i = 0; i < shlen(vt); i++) arrfree(vt[i].value);
  shfree(vt);
  for (int i = 0; i < alen(as); i++) if (as[i]) arrfree(as[i]);
  arrfree(as);
  for (int i = 0; i < alen(bs); i++) if (bs[i]) arrfree(bs[i]);
  arrfree(bs);
  return r;
}

//FIXME: macro could get redefined during expansion
//       for now we just don't free them
static char *macroexpand(ncm_state *this, macro_t *m, char *args, int flags) {
  if (m->depth > NCM_MACRO_DEPTH_LIMIT) {
    fatal("macro depth limit reached, while expanding `%s`", m->name);
  }

  this->mex_count++;
  m->depth++;

  char *b = NULL;
  if (m->nargs != -1) b = macroexpand_fn(this, m, args);
  else {
    char *p = m->body;
    for (; *p; p++) aput(b, *p);
    aput(b, 0);
  }
  this->scope_row = m->row;
  this->scope_col = m->col;
  U32 fs = ME_MACRO_SCOPE;
  int standalone = flags&ME_STANDALONE;
  if (standalone) fs |= ME_STANDALONE;
  if (standalone || (m->flags&M_ONE_LINE)) fs |= ME_NO_POSITION;
  char *r = macroexpand2(this, m->filename, b, fs);
  m->depth--;
  return r;
}

static char **parse_cmd_args(char *args) {
  char **as = NULL;
  char *a = NULL;
  char *p = args;
  for (;; p++) {
    if (isspace(*p)) {
      if (a) {
        aput(a, 0);
        aput(as, a);
        a = NULL;
      }
      while (isspace(*p)) p++;
    }
    if (!*p) break;
    if (*p == '\\' && (p[1] == '\\' || isspace(p[1]))) {
      p++;
      aput(a, *p);
    }
    if (*p == '"') {
      p++;
      if (a) {
        aput(a, 0);
        aput(as, a);
        a = NULL;
      }
      for (;; p++) {
        if (*p == '\"' || !*p) {
          if (*p == '\"') p++;
          aput(a, 0);
          aput(as, a);
          a = NULL;
          break;
        }
        if (*p == '\\' && (p[1] == '\\' || p[1] == '\"')) {
          p++;
          aput(a, *p);
        } else {
          aput(a, *p);
        }
      }
    } else {
      aput(a, *p);
    }
  }
  if (a) {
    aput(a, 0);
    aput(as, a);
  }
  return as;
}

static char *cmd_fmt(ncm_state *this, char **as) {
  char buf[128];
  char *r = NULL;
  char *format = as[0];
  int ai = 1;

  for (char *p = format; *p; ) {
    if (*p != '%') {
      aput(r, *p);
      p++;
      continue;
    }
    int pref_char = ' ';
    int pref_count = 0;
    int pref_plus = 0;
    int left_justify = 0;
    p++;
    if (*p == '%') {
      aput(r, *p);
      p++;
      continue;
    }
    for (; *p; p++) { //flags
      if (*p == '0') {
        pref_char = '0';
      } else if (*p == '+') {
        pref_plus = 1;
      } else if (*p == '-') {
        left_justify = 1;
      } else if (*p == '?') {
        p++;
        pref_char = *p;
      } else {
        break;
      }
    }
    if (isdigit(*p)) {
      for (; isdigit(*p); p++) {
        pref_count = pref_count*10 + (*p-'0');
      }
    }
    int type = *p++;
    char *a = as[ai++];
    if (type == 'd' || type == 'x' || type=='X') {
      int sign = 0;
      char *q = a;
      if (*q == '+') q++;
      else if (*q == '-') {
        sign = 1;
        q++;
      }
      U32 v = 0;
      for (; isdigit(*q); q++) {
        v = v*10 + (*q-'0');
      }
      if (type == 'd') {
        sprintf(buf, "%d", v);
      } else if (type == 'x')  {
        sprintf(buf, "%X", v);
      } else {
        sprintf(buf, "%x", v);
      }
      if (sign) {
        pref_count -= 1;
        aput(r, '-');
      } else if (pref_plus) {
        pref_count -= 1;
        aput(r, '+');
      }
      pref_count -= strlen(buf);
      if (!left_justify)
        for (; pref_count>0; pref_count--) aput(r, pref_char);
      aputs(r, buf);
      if (left_justify)
        for (; pref_count>0; pref_count--) aput(r, pref_char);
    } else if (type == 's') {
      pref_count -= strlen(a);
      if (!left_justify)
        for (; pref_count>0; pref_count--) aput(r, pref_char);
      aputs(r, a);
      if (left_justify)
        for (; pref_count>0; pref_count--) aput(r, pref_char);
    } else {
      aput(r, type);
    }
  }
  aput(r, 0);
  return r;
}


static void expand_command(ncm_state *this, char *cmd) {
  char *result = 0;
  char **as = NULL;
  char *b = NULL;
  if (*cmd == '\"') {
    char **as = parse_cmd_args(cmd);
    b = cmd_fmt(this, as);
  } else {
    if (!this->opt.command) return;
    char *r = this->opt.command(this, cmd);
    if (!r) return;
    for (char *p = r; *p; p++) aput(b, *p);
    aput(b, 0);
    free(r);
  }
  if (as) {
    //FIXME: free as
    for (int i = 0; i < alen(as); i++) arrfree(as[i]);
    arrfree(as);
  }
  if (!b) return;
  //expand the result of the command
  this->scope_row = filep->row;
  this->scope_col = filep->col;
  macroexpand2(this, filep->file->name, b, ME_MACRO_SCOPE);
}

static char *get_comment(ncm_state *this) {
  int keep = this->opt.flags&NCM_KEEP_COMMENTS;
  //int keep = 1;
  char *r = NULL;

  int ch = pop_char();
  if (keep) aput(r, ch);

  if (next_char() == '/') {
    for (;;) {
      int ch = next_char();
      if (!ch || ch == '\n') break;
      pop_char();
      if (keep) aput(r, ch); else aput(r, ' ');
    }
    aput(r, 0);
    return r;
  }

  ch = pop_char();
  if (keep) aput(r, ch);

  int depth = 0;
  for (;;) {
    int ch = pop_char();
    if (keep || ch == '\n') aput(r, ch);
    else aput(r, ' ');
    if (ch == '/' && next_char() == '*') {
      depth++;
      ch = pop_char();
      if (keep) aput(r, ch); else aput(r, ' ');
    } else if (ch == '*' && next_char() == '/') {
      ch = pop_char();
      if (keep) aput(r, ch); else aput(r, ' ');
      if (!depth) break;
      depth--;
    } else if (!ch) {
      break;
    }
  }

  aput(r, 0);
  return r;
}

static void copy_till_newline(ncm_state *this) {
  for (;;) {
    int ch = pop_char();
    if (ch == '\n') {
      put_char(ch);
      break;
    } else if (ch == '\\') {
      put_char(ch);
      put_char(pop_char());
    } else if (!ch) {
      break;
    } else {
      put_char(ch);
    }
  }
}

static S32 eval_log2(U32 v) {
  S32 r = 0;
  while (v) {
    v >>= 1;
    r++;
  }
  return r ? r-1 : r;
}


static S32 eval_term(ncm_state *this) {
  int def_check = 0;
  skipws(this, SKIPWS_ESC_NL);
  int ch = next_char();
  if (ch == '(') {
    pop_char();
    S32 v = eval_expr(this);
    expect_char(')');
    return v;
  } else if (isdigit(ch)) {
    S32 v;
    if (ch == '0' && filep->ptr[1] == 'x') {
      pop_char();
      pop_char();
      char *s = get_hex(this);
      v = strtol(s, 0, 16);
      arrfree(s);
    } else {
      char *s = get_dec(this);
      v = strtol(s, 0, 10);
      arrfree(s);
    }
    return v;
  } else if (issymchr(ch)) {
symbol:;
    char *name = get_sym(this);
    if (!strcmp(name, "log2")) {
      S32 a = eval_term(this);
      arrfree(name);
      return eval_log2(a);
    }
    macro_t *m = shget(this->mt,name);
    char *s = 0;
    if (m) s = m->body;
    if (!s && this->at) s = shget(this->at, name);
    arrfree(name);
    if (!s) return 0;
    if (def_check) return 1;
    return strtol(s, 0, 10);
  } else if (ch == MCH) {
    pop_char();
    skipws(this, SKIPWS_ESC_NL);
    if (!issymchr(next_char())) fatal("Unexpected `%c`", ch);
    def_check = 1;
    goto symbol;
  } else if (ch == '-' || ch == '+' || ch == '!' || ch == '~') {
    pop_char();
    S32 v = eval_term(this);
    if (ch == '-') v = -v;
    else if (ch == '!') v = !v;
    else if (ch == '~') v = ~(U32)v;
    return v;
  }
  return 0;
}

static S32 eval_mul(ncm_state *this) {
  S32 l = eval_term(this);
again:
  skipws(this, SKIPWS_ESC_NL);
  int ch = next_char();
  if (ch == '*' || ch == '/' || ch == '%') {
    pop_char();
    S32 r = eval_term(this);
    if (ch == '*') l *= r;
    else {
      if (r == 0) l = 0;
      else if (ch == '/') l /= r;
      else l %= r;
    }
    goto again;
  }
  return l;
}

static S32 eval_add(ncm_state *this) {
  S32 l = eval_mul(this);
again:
  skipws(this, SKIPWS_ESC_NL);
  int ch = next_char();
  if (ch == '+' || ch == '-') {
    pop_char();
    S32 r = eval_mul(this);
    if (ch == '+') l += r;
    else l -= r;
    goto again;
  }
  return l;
}

static S32 eval_shift(ncm_state *this) {
  S32 l = eval_add(this);
again:
  skipws(this, SKIPWS_ESC_NL);
  int ch = next_char();
  if (ch == '<' || ch == '>') {
    pop_char();
    if (next_char() != ch) {
      unpop_char();
      return l;
    }
    S32 r = eval_add(this);
    if (ch == '<') l = (U32)l << (U32)r;
    else l = (U32)l >> (U32)r;
    goto again;
  }
  return l;
}

static S32 eval_cmp(ncm_state *this) {
  int cycle = 0;
  int t = 1;
  S32 l = eval_shift(this);
again:
  skipws(this, SKIPWS_ESC_NL);
  int ch = next_char();
  if (ch == '<' || ch == '>' || ch == '=' || ch == '!') {
    pop_char();
    int ch2 = next_char();
    if (ch2 == '=') { 
      pop_char();
    } else if ((ch == '<' && ch2 == '<') || (ch == '>' && ch2 == '>')) {
      goto end;
    }
    S32 r = eval_shift(this);
    if (t) { //cant return immediately, since all parts have to be consumed
      if (ch == '=') t = l == r;
      else if (ch == '!') t = l != r;
      else if (ch == '<' && ch2 == '=') t = l <= r;
      else if (ch == '>' && ch2 == '=') t = l >= r;
      else if (ch == '<') t = l < r;
      else t = l > r;
    }
    l = r;
    cycle++;
    goto again;
  }
end:
  if (cycle) return t;
  return l;
}

static S32 eval_bitwise(ncm_state *this) {
  S32 l = eval_cmp(this);
again:
  skipws(this, SKIPWS_ESC_NL);
  int ch = next_char();
  if (ch == '&' || ch == '|' || ch == '^') {
    pop_char();
    S32 r = eval_cmp(this);
    if (ch == '&') l = (U32)l & (U32)r;
    else if (ch == '|') l = (U32)l | (U32)r;
    else l = (U32)l ^ (U32)r;
    goto again;
  }
  return l;
}

static S32 eval_logic(ncm_state *this) {
  int cycle = 0;
  S32 l = eval_bitwise(this);
  S32 t = l != 0;
again:
  skipws(this, SKIPWS_ESC_NL);
  int ch = next_char();
  if (ch == '&' || ch == '|') {
    pop_char();
    int ch2 = next_char();
    if (ch2 != ch) {
      unpop_char();
      goto end;
    }
    pop_char();
    S32 r = eval_bitwise(this);
    if (ch == '&') t = (t && r) ? 1 : 0;
    else t = (t || r) ? 1 : 0;
    l = r;
    cycle++;
    goto again;
  }
end:
  if (cycle) return t;
  return l;
}

static S32 eval_expr(ncm_state *this) {
  return eval_logic(this);
}

static void process_scope(ncm_state *this, int doexpand, int base_scope) {
  //skipws(this, 1);
  this->scope_col = filep->col;
  this->scope_row = filep->row;
  char *body = get_cond_body(this);
  if (doexpand) {
    U32 flags = 0;
    if (base_scope) flags |= ME_BASE_SCOPE;
    macroexpand2(this, filep->file->name, body, base_scope);
  } else {
    arrfree(body);
  }
  emit_position(this);
}


static char *get_filename(ncm_state *this) {
  int term;
  char *r = NULL;
  if (next_char() == '<') {
    term = '>';
    aput(r,pop_char());
  } else if (next_char() == '\"') {
    term = '\"';
    pop_char();
  } else {
    term = ' ';
  }
  for (;;) {
    int ch = pop_char();
    if (!ch)  break;
    if (term == ' ' && isspace(ch)) break;
    if (term != ' ' && ch == term) break;
    if (ch == '\\') {
      aput(r,pop_char());
    } else {
      aput(r,ch);
    }
  }
  aput(r, 0);
  return r;
}


static void process_file(ncm_state *this) {
  int if_else_glue = -1;
  int norec_def = 0;
  filep_t *csfp = cur_scope(this);
  if (filep->file->included>1 && !strcmp(csfp->file->url->ext,"h")) {
once_escape:
    for (;;) {
      int ch = pop_char();
      if (ch == '#' && issymchr(next_char())) {
        char *name = get_sym(this);
        if (!strcmp(name,"multi")) {
          arrfree(name);
          goto multi;
        }
        arrfree(name);
      } else if (!ch) {
        break;
      } else {
        if (ch == '\n') { //FIXME: replace line count mainteance with
                          //       #line 
          put_char(ch);
        }
      }
    }
    return;
  }
multi:
  for (;;) {
    skipws(this, 1);
    int ch = next_char();
    //printf("%c\n", next_char());
    if (ch == MCH) {
      pop_char();
      int ieg = if_else_glue;
      if_else_glue = -1;
      int escaped = 0;
      if (next_char() == MCH) { //escape the # character
        put_char(pop_char());
        continue;
      } else if (next_char() == ':') { //special include
        //FIXME: process #<> and #[] inside
        //FIXME: add support for `,`
        pop_char();
        int type = next_char();
        if (type == '#') {
          norec_def = 1;
          continue;
        } else if (type == '{') {
          char *b = get_body(this, 0);
          put_char(MCH);
          put_char(':');
          put_char('{');
          put_cstr(this, b);
          put_char('}');
          continue;
        }
        char *name = get_filename(this);
        expand_file2(this, name);
        arrfree(name);
        continue;
      } else if (next_char() == '<') { //#<> symbol
        pop_char();
        goto symbol;
      } else if (next_char() == '[') { //expression evaluation
        pop_char();
        S32 result = eval_expr(this);
        expect_char(']');
        put_fmt(this, "%d", result);
        continue;
      } else if (next_char() == ' ') { //line number (Clang convention)
        put_cstr(this, "#");
        copy_till_newline(this);
        continue;
      } else if (next_char() == '{') { //scope
        //FIXME: copy on write
        macro_tbl_t smt = this->mt;
        aput(this->scopes, smt);
        macro_tbl_t mt = NULL;
        for (int i = 0; i < shlen(smt); i++) {
          shput(mt, smt[i].key, smt[i].value);
        }
        this->mt = mt;
        char *body = get_body(this, 0);
        macroexpand2(this, filep->file->name, body, ME_MACRO_SCOPE);
        this->mt = apop(this->scopes);
        shfree(mt);
        continue;
      } else if (next_char() == '(') { //shell command
        char *cmd = read_parens(this, '(', ')', '\\');
        //int flags = ME_STANDALONE;
        //cmd2 = macroexpand2(this, filep->file->name, cmd, flags);
        int flags = 0;
        char *c = inject_vars(this, "command", cmd, 0, flags);
        arrfree(cmd);
        expand_command(this, c);
        arrfree(c);
        continue;
      } else if (next_char() == '\\') {
        //allow redefining < and :
        pop_char();
        escaped = 1;
        //if (next_char() == '{') {...} //the body escaped from expansion
      }
      char *name = issymchr(next_char()) ? get_sym(this) : get_op(this);
      if (escaped && issymchr(name[0])) {
        //escape macro for the old macro processor
        put_cstr(this, "#");
        put_cstr(this, name);
        arrfree(name);
        copy_till_newline(this);
        continue;
      }

      if (!strcmp(name,"if")) {
        arrfree(name);
        S32 cnd_result = eval_expr(this);
        if (next_char() == '\n') pop_char();
        process_scope(this, cnd_result, 1);
        skipws(this, 1);
        if (next_char() == MCH) if_else_glue = cnd_result;
        continue;
      } else if (!strcmp(name,"elif")) {
        arrfree(name);
        if (ieg == -1) fatal("Unexpected `#elif`");
        S32 cnd_result;
        if (ieg) {
          cnd_result = 1;
          process_scope(this, 0, 1);
        } else {
          cnd_result = eval_expr(this);
          if (next_char() == '\n') pop_char();
          process_scope(this, cnd_result, 1);
        }
        skipws(this, 1);
        if (next_char() == MCH) if_else_glue = cnd_result;
        continue;
      } else if (!strcmp(name,"else")) {
        arrfree(name);
        if (ieg == -1) fatal("Unexpected `#else`");
        process_scope(this, !ieg, 1);
        continue;
      } else if (!strcmp(name,"endif")) {
        skipws(this,SKIPWS_NO_NL);
        if (next_char() == '\n') pop_char();
        arrfree(name);
        continue;
      } else if (!strcmp(name,"multi")) {
        arrfree(name);
        continue;
      } else if (!strcmp(name,"once")) {
        arrfree(name);
        if (filep->file->included>1) goto once_escape;
        continue;
      } else if (!strcmp(name,"undef")) {
        arrfree(name);
        skipws(this,1);
        char *n = issymchr(next_char()) ? get_sym(this) : get_op(this);
        macro_t *m = shget(this->mt, n);
        shdel(this->mt, n);
        for (int i = (int)alen(this->scopes)-1; i >= 0; i--) {
          if (shget(this->scopes[i], n) == m) {
            shdel(this->scopes[i], n);
          }
        }
        continue;
      } else if (!strcmp(name,"line") || !strcmp(name,"include")) {
        put_cstr(this, "#");
        put_cstr(this, name);
        arrfree(name);
        copy_till_newline(this);
        continue;
      }

      char *args = 0;
      if (next_char() == '(') args = read_parens(this, '(', ')', '\\');
      skipws(this, 1);
      int row = filep->row;
      int col = filep->col;
      char *filename = filep->file->name;
      int flags = 0;
      if (norec_def) {
        flags |= M_NOREC;
        norec_def = 0;
      }
      char *body = get_body(this, &flags);
      macro_t *m = shget(this->mt,name);
      if (!m) {
        m = add_macro(this, name, args, body, row, col, filename);
      } else { //redefinition
        arrfree(m->body);
        m->body = body;
        arrfree(name);
      }
      if (filep->row != row) flags &= ~(U32)M_ONE_LINE;
      m->flags |= flags;
      arrfree(args);
      if (!(flags&M_ONE_LINE)) emit_position(this);
    } else if (issymchr(ch)) {
symbol:;
      char *name = issymchr(next_char()) ? get_sym(this) : get_op(this);
      macro_t *m = shget(this->mt,name);
      if (ch==MCH) skipws(this, 0);
      if (ch==MCH && next_char() == '=') {
        char *s = name;
        pop_char();
        U32 srow = filep->row;
        U32 scol = filep->col;
        char *v = NULL;
        for (;;) {
          int c = pop_char();
          if (!c || c == '>') break;
          aput(v, c);
        }
        aput(v,0);
        filep->row = srow;
        filep->col = scol;
        v = macroexpand2(this, filep->file->name, v
                   , ME_STANDALONE|ME_NO_POSITION|ME_BASE_SCOPE);
        if (!m) {
          add_macro(this, s, 0, v, filep->row, filep->col, filep->file->name);
        } else {
          arrfree(m->body);
          m->body = v;
          arrfree(s);
        }
        continue;
      }
#define SKIP_TRAIL_GT() if (ch == MCH && next_char() == '>') pop_char()
      if (!m || ((m->flags&M_NOREC) && m->depth)) {
        if (ch == MCH) {
          put_char(MCH);
          put_char('<');
        }
        put_cstr(this,name);
      } else {
        char *args = NULL;
        if (m->nargs != -1) {
          if (next_char() != '(') {
            if (this->opt.flags&NCM_PARENLESS_ARGS) {
              //treat everything till end of line as arg list
              int depth = 0;
              for (;;) {
                int ch = next_char();
                if (!ch || ch == '\n') break;
                if (ch == ')') {
                  if (!depth) break;
                  depth--;
                  aput(args, ch);
                  continue;
                }
                pop_char();
                if (ch == '/' && next_char() == '/') {
                  unpop_char();
                  break;
                }
                if (ch == '(') depth++;
                aput(args, ch);
              }
              aput(args, 0);
            } else {
              aput(args, 0);
            }
          } else {
            args = read_parens(this, '(', ')', '\\');
          }
        }
        abody_t sabody = this->abody;
        char *abody = NULL;
        if (m->bodyarg != M_NO_BODY) {
          skipws(this, 1);
          if (next_char() != '{') {
            fatal("no {}-body for macro `%s`", m->name);
          }
          this->abody.row = filep->row;
          this->abody.col = filep->col;
          abody = read_parens(this, '{', '}', '\\');
          this->abody.ptr = abody;
        }
        macroexpand(this, m, args, 0);
        this->abody = sabody;
        if (args) arrfree(args);
        if (abody) arrfree(abody);
        SKIP_TRAIL_GT();
      }
      arrfree(name);
    } else if (isquote(ch)) {
      int term = pop_char();
      put_char(term);
      for (;;) {
        ch = pop_char();
        put_char(ch);
        if (!ch) break;
        if (ch == term) break;
        if (ch == '\\') put_char(pop_char());
      }
    } else if (isopchr(ch)) {
      goto symbol;
    } else if (!ch) {
      break;
    } else {
      put_char(pop_char());
    }
  }
}

static rfile_t *new_rfile(char *name, U8 *data, U32 size) {
  rfile_t *f = malloc(sizeof(rfile_t));
  f->name = strdup(name);
  f->data = data;
  f->size = size;
  f->included = 0;
  f->flags = 0;
  f->url = 0;
  return f;
}

static void delete_rfile(rfile_t *f) {
  if (f->url) free(f->url);
  free(f->name);
  arrfree(f->data);
  free(f);
}

static rfile_t *rfile_open(ncm_state *this, char *filename) {
  rfile_t *f = shget(this->ft,filename);
  if (f) return f;
  U32 size;
  U8 *data = this->opt.file_get(this, &size, filename);
  if (!data) fatal("Couldn't read `%s`", filename);
  f = new_rfile(filename, data, size);
  f->url = url_parts(f->name);
  //printf("%s,%s,%s\n", f->url->name, f->url->ext, f->url->dir);
  shput(this->ft, f->name, f);
  return f;
}

static filep_t *new_filep(rfile_t *f) {
  filep_t *fp = malloc(sizeof(filep_t));
  fp->file = f;
  fp->start = f->data;
  fp->ptr = fp->start;
  fp->end = fp->start + f->size;
  fp->col = 0;
  fp->pcol = 0;
  fp->row = 0;
  fp->prev = 0;
  return fp;
}

static void delete_filep(filep_t *fp) {
  free(fp);
}


static void open_buffer(ncm_state *this, char *name, U8 *content, U32 size) {
  rfile_t *f = new_rfile(name, content, size);
  f->flags |= F_BUFFER;
  filep_t *fp = new_filep(f);
  fp->prev = filep;
  filep = fp;
}

static void close_buffer(ncm_state *this) {
  filep_t *fp = filep;
  filep = fp->prev;
  delete_rfile(fp->file);
  delete_filep(fp);
}

static char *resolve_file(ncm_state *this, char *rel_name) {
  char *tmprel_name = 0;
  char *tmpname = 0;
  int nonlocal = 0;
  if (*rel_name == '<') {
    nonlocal = 1;
    rel_name++;
  }
  filep_t *cfp = cur_filep(this);
  char **ps = this->paths;
  url_t *url = url_parts(rel_name);
  if (!*url->ext) {
    tmprel_name = cat(rel_name, ".h");
    rel_name = tmprel_name;
  }
  free(url);
  for (int i = -1; i < 0 || *ps; i++) {
    char *folder;
    if (i == -1) {
      if (nonlocal || !cfp) {
        continue;
      }
      folder = cfp->file->url->dir; //try current dir
    } else {
      folder = *ps;
      ps++;
    }
    tmpname = cat(folder, rel_name);
    if (this->opt.file_exist(this,tmpname)) break;
    free(tmpname);
    tmpname = 0;
  }
  if (tmprel_name) free(tmprel_name);
  return tmpname;
}

//FIXME: should the `#line` be used instead?
static void emit_position(ncm_state *this) {
  if (!filep) return;
  if (this->opt.flags&NCM_NO_LINE_NUMS) return;
  filep_t *cfp = filep;
  int row = cfp->row+1;
  int col = cfp->col+1;
  char *name = cfp->file->name;
  char *s;
  this->position_count++;
  if (this->col) put_char('\n');
#if 1
  if (cfp->file->flags&F_PRIVATE) { //base file
    put_fmt(this, "#line %d \"<%s>\"\n", row, name);
  } else {
    put_fmt(this, "#line %d \"%s\"\n", row, name);
  }
#else
  if (cfp->file->flags&F_PRIVATE) { //base file
    put_fmt(this, "#line %d \"<%s>\" %d\n", row, name, col);
  } else {
    put_fmt(this, "#line %d \"%s\" %d\n", row, name, col);
  }
  
#endif
}

static void open_file(ncm_state *this, char *rel_name) {
  char *resolved_name = 0;
  char *filename;
  if (filep) resolved_name = resolve_file(this, rel_name);
  if (resolved_name) filename = resolved_name;
  else filename = rel_name; //consider it being absolute name
  rfile_t *f = rfile_open(this, filename);
  if (this->include_depth > NCM_INCLUDE_DEPTH_LIMIT) {
    fatal("Include depth limit reached,\n  while including `%s`", filename);
  }
  this->include_depth++;
  f->included++;
  f->flags |= F_BASE;
  filep_t *fp = new_filep(f);
  fp->prev = filep;
  filep = fp;
  if (resolved_name) free(resolved_name);
  emit_position(this);
}

static void close_file(ncm_state *this) {
  this->include_depth--;
  filep_t *fp = filep;
  filep = fp->prev;
  delete_filep(fp);
  emit_position(this);
}

static void expand_file2(ncm_state *this, char *filename) {
  open_file(this, filename);
  process_file(this);
  close_file(this);
}

static ncm_state *new_ncm() {
  ncm_state *this = malloc(sizeof(ncm_state));
  memset(this, 0, sizeof(ncm_state));
  return this;
}

static void del_macro(macro_t *m) {
  arrfree(m->name);
  arrfree(m->body);
  free(m->filename);

  for (int i = 0; i < alen(m->ds); i++) arrfree(m->ds[0]);
  arrfree(m->ds);

  for (int i = 0; i < alen(m->args); i++) arrfree(m->args[0]);
  arrfree(m->args);
  free(m);
}

static void del_ncm(ncm_state *this) {
  shfree(this->mt);
  for (int i = 0; i < alen(this->ml); i++) {
    del_macro(this->ml[i]);
  }
  arrfree(this->ml);

  for (int i = 0; i < shlen(this->ft); i++) {
    delete_rfile(this->ft[i].value);
  }
  shfree(this->ft);

  arrfree(this->scopes);

  free(this);
}

ncm_options_t ncm_default_options() {
  ncm_options_t o;
  memset(&o, 0, sizeof(o));
  o.mchar = '#';
  return o;
}

static void expand_line_macro(ncm_state *this) {
  char *filename = NULL;
  int row = 1;
  char *r = NULL;
  for (char *p = (char*)this->out; *p; ) {
    if (!strncmp(p, "#line ", 6)) {
      char *t;
      char *s = p;
      char *q = p + 6;
      row = strtol(q, &q, 10);
      if (filename) {
        arrfree(filename);
        filename = NULL;
      }
      if (*q == ' ') q++;
      for (; *q && *q != '\n'; q++) aput(filename, *q);
      aput(filename, 0);
      for (; p < q; p++) aput(r, *p);
      if (*p == '\n') {
        aput(r, *p);
        p++;
      }
#if 1
skipped_dup_line:
      q = p;
      while (isspace(*q)) q++;
      if (strncmp(q, "#line ", 6)) continue;
      t = s;
      while(*q && *q == *t) {
        if (*q == '\n') {
          p = q+1;
          goto skipped_dup_line;
          
        }
        q++;
        t++;
      }
#endif
      continue;
    }
    for (; *p && *p != '\n'; ) {
      if (!issymchr(*p)) {
        if (p[0] == MCH && p[1] == ':' && p[2] == '{') {
          /*aput(r, ' ');
          aput(r, ' ');
          aput(r, ' ');*/
          p += 3;
          for (;;) {
            if (!*p) break;
            if (*p == '}') {
              //aput(r, ' ');
              p++;
              break;
            }
            if (*p == '\\' && (p[1] == '\\' || p[1] == '}')) {
              p++;
              aput(r, *p);
              continue;
            }
            if (isquote(*p)) {
              int term = *p++;
              aput(r, term);
              for (; *p; p++) {
                if (*p == '\\') {
                  p++;
                  aput(r,*p);
                } else if (*p == term) {
                  aput(r,*p);
                  p++;
                  break;
                } else {
                  aput(r,*p);
                }
              }
              continue;
            }
            aput(r, *p);
            p++;
          }
          continue;
        }
        aput(r, *p);
        p++;
        continue;
      }
      char *q = p;
      for (; issymchr(*q); q++);
      if (q-p == 6 && !strncmp(p, "_LINE_", 6)) {
        p = q;
        char *s = fmt("%d", row);
        aputs(r, s);
        arrfree(s);
      } else if (q-p == 6 && !strncmp(p, "_FILE_", 6)) {
        p = q;
        aputs(r, filename);
      } else {
        while (p < q) {
          aput(r, *p);
          p++;
        }
      }
    }
    if (*p == '\n') {
      aput(r, *p);
      p++;
      row++;
    }
  }
  aput(r, 0);
  arrfree(this->out);
  this->out = (U8*)r;
}

char *ncm_expand_file(ncm_options_t *opt, char *filename) {
  ncm_state *this = new_ncm();
  this->paths = opt->paths;
  this->opt = *opt;
  expand_file2(this, filename);
  aput(this->out, 0);
  if (!(this->opt.flags&NCM_NO_LINE_MACRO)) expand_line_macro(this);
  char *r = (char *)this->out;
  del_ncm(this);
  return r;
}

char *ncm_eval(ncm_options_t *opt, char *name, char *expr) {
  ncm_state *this = new_ncm();
  this->paths = opt->paths;
  this->opt = *opt;
  char *body = NULL;
  aputs(body, expr);
  aput(body, 0);
  macroexpand2(this, name, body, ME_NO_POSITION|ME_BASE_SCOPE);
  aput(this->out, 0);
  if (!(this->opt.flags&NCM_NO_LINE_MACRO)) expand_line_macro(this);
  char *r = (char *)this->out;
  del_ncm(this);
  return r;
}

void ncm_free_result(char *result) {
  arrfree(result);
}

void *ncm_user(void *ncm) {
  ncm_state *this = ncm;
  return this->opt.user;
}


#endif //NCM_IMPLEMENTATION

#endif //NCM_H
