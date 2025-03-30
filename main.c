#include "cauldron.h"
#include <stdio.h>

int main(void) {
  int flag = 4;
  defer(printf("Bye, World!%d\n", flag));
  scope(printf("hello\n"), printf("bye\n")) {
    printf("Hello, World!\n");
    printf("%d\n", flag);
  }
  with_resource(file, "main.c", 0) {
    char buf[1024];
    read(file.fd, buf, sizeof(buf));
    printf("%s", buf);
  }
  printf("%d\n", flag);
}
