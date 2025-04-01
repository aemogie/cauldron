#include "cauldron.h"
#include <stdio.h>

int main(void) {
  int flag = 4;
  /* defer(printf("Bye, World!%d\n", flag)); */
  scope(._x = printf("hello\n"), printf("bye\n"), int _x) {
    printf("Hello, World!\n");
    printf("%d\n", flag);
  }
  with_resource(file, __FILE__, 0) {
    char buf[1024];
    read(state.file.fd, buf, sizeof(buf));
    printf("%s", buf);
  }
  printf("%d\n", flag);
}
