#ifndef UTIL_H
#define UTIL_H

char *_hidden_cat_(char *a0, ...);

#define cat(...) _hidden_cat_(__VA_ARGS__, 0)

char *sjoin(char *a, char *b);
char *sjoin3(char *a, char *b, char *c);
char *sjoin4(char *a, char *b, char *c, char *d);
int begins_with(const char *head, const char *string);

#endif
