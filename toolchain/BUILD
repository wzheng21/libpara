# To see how the toolchain is setup, see
# https://docs.bazel.build/versions/master/tutorial/cc-toolchain-config.html

package(default_visibility = ["//visibility:public"])

#filegroup(name = "clang_suite")

cc_toolchain_suite(
  name = "clang_suite",
  toolchains = {
    "k8": "k8-cc-compiler",
  },
)

load(":cc_toolchain_config.bzl", "cc_toolchain_config")
cc_toolchain_config(
  name = "clang-11-libcxx_k8",
#  cpu = "k8",
)

filegroup(name = "empty")
cc_toolchain(
  name = "k8-cc-compiler",
  toolchain_identifier = "clang-11-libcxx_k8",
  toolchain_config = ":clang-11-libcxx_k8",
  all_files = ":empty",
  compiler_files = ":empty",
  dwp_files = ":empty",
  linker_files = ":empty",
  objcopy_files = ":empty",
  strip_files = ":empty",
  supports_param_files = 0,
)