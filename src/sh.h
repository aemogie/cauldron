#include <unistd.h>

#define echo(...) printf("%s:%d: %s\n", __FILE__, __LINE__, #__VA_ARGS__)

#define SH_TRACE 1

#if SH_TRACE
#define trace(...) printf("$ %s\n", #__VA_ARGS__)
#else
#define trace(...) ((void)0)
#endif

// todo: error checking
#define rm(file) (trace(rm file), unlink(#file))

