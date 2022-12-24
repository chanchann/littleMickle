## 柔性数组

ANSI C标准规定：定义一个数组时，数组的长度必须是一个常数，即数组的长度在编译的时候是确定的。

```c
int a[10];
```

C99标准规定：可以定义一个变长数组

```c
int len;
int a[len];
```

```c
int a[0];

sizeof(a);  // 0
```

## 使用

一般作为成员

```c
struct buffer {
  int len;
  char a[0];
}
```

```c
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
```

## 优点 

灵活地申请内存空间，以满足不同大小的数据

这个零长度数组又不占用结构体的存储空间

## 为什么不使用指针来代替零长度数组？

```c
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
```

