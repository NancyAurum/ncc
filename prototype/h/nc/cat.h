#:pp
#:mem

char *cat_imp_(char *a0, ...);
#cat([xs]) cat_imp_(pp_map(nsh_cstr,xs),(char*)0)


void say_imp_(int count, ...);
#say([xs]) {do {
  mBegin(0);
  say_imp_(xs_n,pp_map(nsh_cstr,xs)); \
  mEnd();
} while (0)}
