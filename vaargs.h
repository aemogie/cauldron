#define count_variadic(...)                                                    \
  count_variadic_impl(__VA_ARGS__ __VA_OPT__(, ) 15, 14, 13, 12, 11, 10, 9, 8, \
                      7, 6, 5, 4, 3, 2, 1, 0)

#define count_variadic_impl(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, \
                            _13, _14, _15, N, ...)                             \
  N

#define __for_each_expand2(count) for_each_impl_##count
#define __for_each_expand(count) __for_each_expand2(count)
#define for_each(op, ...)                                                      \
  __for_each_expand(count_variadic(__VA_ARGS__))(op, __VA_ARGS__)

#define for_each_impl_0(op, x) // noop
#define for_each_impl_1(op, x, ...) op(x) for_each_impl_0(op, __VA_ARGS__)
#define for_each_impl_2(op, x, ...) op(x) for_each_impl_1(op, __VA_ARGS__)
#define for_each_impl_3(op, x, ...) op(x) for_each_impl_2(op, __VA_ARGS__)
#define for_each_impl_4(op, x, ...) op(x) for_each_impl_3(op, __VA_ARGS__)
#define for_each_impl_5(op, x, ...) op(x) for_each_impl_4(op, __VA_ARGS__)
#define for_each_impl_6(op, x, ...) op(x) for_each_impl_5(op, __VA_ARGS__)
#define for_each_impl_7(op, x, ...) op(x) for_each_impl_6(op, __VA_ARGS__)
#define for_each_impl_8(op, x, ...) op(x) for_each_impl_7(op, __VA_ARGS__)
#define for_each_impl_9(op, x, ...) op(x) for_each_impl_8(op, __VA_ARGS__)
#define for_each_impl_10(op, x, ...) op(x) for_each_impl_9(op, __VA_ARGS__)
#define for_each_impl_11(op, x, ...) op(x) for_each_impl_10(op, __VA_ARGS__)
#define for_each_impl_12(op, x, ...) op(x) for_each_impl_11(op, __VA_ARGS__)
#define for_each_impl_13(op, x, ...) op(x) for_each_impl_12(op, __VA_ARGS__)
#define for_each_impl_14(op, x, ...) op(x) for_each_impl_13(op, __VA_ARGS__)
#define for_each_impl_15(op, x, ...) op(x) for_each_impl_14(op, __VA_ARGS__)
#define for_each_impl_16(op, x, ...) op(x) for_each_impl_15(op, __VA_ARGS__)

struct file {
  int fd;
};
