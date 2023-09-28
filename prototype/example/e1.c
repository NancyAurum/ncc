#include "stdio.h"

int &int."[]"(int bit) {
  return ((*this)>>bit)&1;
}

/*
int &int."[]="(int bit, int val) {
  uint32_t sb = (uint32_t)1<<bit;
  *this = ((uint32_t)*this & ~(uint32_t)1<<bit) | ((uint32_t)val << bit);
  return this;
}
*/

int main() {
  int x;
  x[20] = 123;

  return 0;
}
