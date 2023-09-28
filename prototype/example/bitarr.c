#include <stdio.h>
#include <stdint.h>

int int."[]"(int bit) {
  return ((*this)>>bit)&1;
}

int &int."[]="(int bit, int val) {
  uint32_t sb = (uint32_t)1<<bit;
  *this = ((uint32_t)*this & ~(uint32_t)1<<bit) | ((uint32_t)val << bit);
  return this;
}


int main() {
  int x = 123;
  if (x[0]) printf("%d is odd\n", x);
  else printf("%d is even\n", x);
  
  x[0] = 0;

  if (x[0]) printf("%d is odd\n", x);
  else printf("%d is even\n", x);

  return 0;
}
