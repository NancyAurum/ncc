class C {
  int *m_elts;
  int m_size;
  int m_used;
}

C *C.ctor {
  return 0;
}

C *C.dtor {
  return 0;
}

C *C."="(C *b) {
  return this;
}


int foo() {
  C o, v;
  o = v;
}
