#include <unistd.h>

#define echo(...) printf("%s:%d: %s\n", __FILE__, __LINE__, #__VA_ARGS__)

// todo: error checking
#define rm(file) (echo(!rm file), unlink(#file))
