class C {
  int *m_elts;
  int m_size;
  int m_used;
}

C *C.ctor {
  return 0;
}

//copy constructor for assignments and returning
C *C.ctor_C(C *a) {
  return 0;
}

C *C.dtor {
  return 0;
}

C *C."="(C a) {
  return 0;
}


C foo() {
  C o;
  1+2;
  return o;
}

void bar() {
  C v = foo();
}
