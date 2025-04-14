#include "cauldron.h"
#include "sh.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char **argv) {
  echo(Hello, World!);
  rm(build/bin/main);
  char *buf;
  echo(buffer declared);
  defer {
    free(buf);
    echo(buffer freed);
  };
  buf = malloc(100);
  echo(allocated buffer);
}
