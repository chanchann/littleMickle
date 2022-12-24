#include <stdio.h>
#include <stdlib.h>

struct buffer1 {
  int len;
  int a[0];
};

struct buffer2 {
  int len;
  int *a;
};

int main() {
  printf("buffer1 : %zu\n", sizeof(struct buffer1)); // 4

  printf("buffer2 : %zu\n", sizeof(struct buffer2)); // 16

  return 0;
}
