#include "vaargs.h"
#include <fcntl.h>
#include <stdbool.h>
#include <unistd.h>

#if defined(__clang__)
#error Clang does not support nested functions. Please use GCC instead.
#elif !defined(__GNUC__)
#error This uses GCC-specific extensions, please use a GNUC compatible C compiler.
#endif

#define _(x) __id_impl(x, __LINE__)
#define __id_impl(name, line) __id_impl2(name, line)
#define __id_impl2(name, line) __##name##_##line

#define __inline_struct_member(arg) arg;
#define inline_struct(...)                                                     \
  struct _(inline) {                                                           \
    for_each(__inline_struct_member, __VA_ARGS__);                             \
  }

#define scope(on_enter, on_exit, ...)                                          \
  for (inline_struct(bool _(flag), __VA_ARGS__)                                \
           state = {._(flag) = true, on_enter};                                \
       state._(flag); state._(flag) = (on_exit, false))

#define defer(expr)                                                            \
  void inline _(deferred)(void *_) { expr; };                                  \
  __attribute__((cleanup(_(deferred)))) void *_(defer) = NULL;

#define with_resource(res_type, ...)                                           \
  scope(.res_type = res_type##_open(__VA_ARGS__),                            \
        res_type##_close(&state.res_type), struct res_type res_type)

// TODO: move these and includes to impl
struct file {
  int fd;
};

struct file file_open(const char *filename, int flags) {
  return (struct file){.fd = open(filename, flags)};
}

void file_close(struct file *file) {
  close(file->fd);
  file->fd = 0;
}
