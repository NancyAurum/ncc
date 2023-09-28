class CC {
  int x;
}

void CC.hello {
  printf("CC.hello\n");
}

class C {
  CC parent;
  int y;
}

CC *C."." {
  return &parent;
}

void test() {
  C o;
  o.hello;
}
