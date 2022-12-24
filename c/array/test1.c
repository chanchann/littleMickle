#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct buffer {
  int len;
  char a[0];
};

int main() {
  struct buffer *buf;
  buf = (struct buffer *)malloc(sizeof(struct buffer) + 12);
  buf->len = 12;
  strcpy(buf->a, "hello world");
  puts(buf->a);

  free(buf);
  return 0;
}
