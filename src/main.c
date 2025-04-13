#include "cauldron.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  char *buf;
  printf("buffer declared %p\n", buf);
  defer {
    free(buf);
    printf("buffer freed %p\n", buf);
  };
  buf = malloc(100);
  printf("allocated buffer %p\n", buf);
}
