class CLst {
  int size;
  int *xs;
}

int CLst."[]"(int index) {
  return this->xs[index];
}

void foo() {
  CLst &a;
  a[123];
}
