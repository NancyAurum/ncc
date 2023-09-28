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

int foo() {
  C o, v;
  1+2;
  while(1) {
    C x;
    {
      lbl:;
      4+5;
      C y;
      goto lbl;
      6+7;
      continue;
    }
  }
}
