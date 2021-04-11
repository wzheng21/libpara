package(default_visibility = ["//visibility:public"])

# https://docs.bazel.build/versions/master/be/c-cpp.html#cc_library
cc_library(
    name = "testing_main",
    testonly = True,
    srcs = ["testing_main.cc",],
    deps = ["@gtest//:gtest",],
)
