#include <stdbool.h>

#if defined(__clang__)
#error Clang does not support nested functions. Please use GCC instead.
#elif !defined(__GNUC__)
#error This uses GCC-specific extensions, please use a GNUC compatible C compiler.
#endif

#define genid() __genid1(__COUNTER__)
#define __genid1(counter) __genid2(counter)
#define __genid2(counter) _##counter

#define defer __defer(genid(), genid())
#define __defer(fn, var)                                                       \
  auto __attribute__((always_inline)) void fn(void *_);                        \
  __attribute__((unused)) __attribute__((cleanup(fn))) void *var;              \
  __attribute__((always_inline)) inline void fn(void *_)

#define alloc(pointer, size) __attribute__((cleanup(free)) *name = malloc(size))
