workspace(
    name = "para",
)

load(
    "@bazel_tools//tools/build_defs/repo:git.bzl",
    "git_repository",
    "new_git_repository"
)

load(
    "@bazel_tools//tools/build_defs/repo:http.bzl",
    "http_archive",
    "http_file"
)

git_repository(
    name = "glog",
    remote = "https://github.com/google/glog.git",
    commit = "96a2f23dca4cc7180821ca5f32e526314395d26a", # tag = "v0.4.0"
)

git_repository(
    name = "gtest",
    remote = "https://github.com/google/googletest.git",
    commit = "703bd9caab50b139428cea1aaff9974ebee5742e", # tag = "release-1.10.0"
)

git_repository(
    name = "gflags",
    remote = "https://github.com/gflags/gflags.git",
    commit = "e171aa2d15ed9eb17054558e0b3a6a413bb01067", # tag = "v2.2.2"
)
