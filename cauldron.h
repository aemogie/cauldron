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

// FIXME: i dont like this on_enter pollution
#define scope(on_enter, on_exit)                                               \
  on_enter;                                                                    \
  for (bool _(flag) = (true); _(flag); _(flag) = (on_exit, false))

#define defer(expr)                                                            \
  void inline _(deferred)(void *_) { expr; };                                  \
  __attribute__((cleanup(_(deferred)))) void *_(defer) = NULL;

#define with_resource(res_type, ...)                                           \
  scope(struct res_type res_type = res_type##_open(__VA_ARGS__),               \
        res_type##_close(&res_type))

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
