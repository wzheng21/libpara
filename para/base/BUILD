# https://docs.bazel.build/versions/master/be/c-cpp.html#cc_library
cc_library(
  name = "base",
  srcs = [],
  hdrs = ["mutex.h",],
  deps = [],
)

cc_test(
  name = "mutex_test",
  srcs = ["mutex_test.cc"],
  deps = [
    "//testing:testing_main",
    ":base",
  ]
)
