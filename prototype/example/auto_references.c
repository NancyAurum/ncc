
void test() {
  int x = 123;
  auto &xref = x; //xref now acts as a proxy for x
  xref = 456;
  printf("%d\n", x); //prints 456
}
