#include "cauldron.h"
#include <stdio.h>

int main(void) {
  int flag = 4;
  defer(printf("Bye, World!%d\n", flag));
  scope(printf("hello\n"), printf("bye\n")) {
    printf("Hello, World!\n");
    printf("%d\n", flag);
  }
  printf("%d\n", flag);
}
