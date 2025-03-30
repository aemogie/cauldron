#include <stdbool.h>
// clang doesnt support nested functions
#if defined(__clang__)
#error Clang doesn't support nested functions. Please use GCC instead.
#elif !defined(__GNUC__)
#error This uses GCC-specific extensions, please use a GNUC compatible C compiler.
#endif

#define _(x) __id_impl(x, __LINE__)
#define __id_impl(name, line) __id_impl2(name, line)
#define __id_impl2(name, line) __##name##_##line

#define scope(on_enter, on_exit)                                               \
  for (bool _(flag) = (on_enter, true); _(flag); _(flag) = (on_exit, false))

#define defer(expr)                                                            \
  void inline _(deferred)(void *_) { expr; };                                  \
  __attribute__((cleanup(_(deferred)))) void *_(defer) = NULL;
