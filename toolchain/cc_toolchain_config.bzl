# To see how the toolchain is setup, see
# https://docs.bazel.build/versions/master/tutorial/cc-toolchain-config.html

load("@bazel_tools//tools/cpp:cc_toolchain_config_lib.bzl",
    "feature",
    "feature_set",
    "flag_group",
    "flag_set",
    "tool_path",
    # "with_feature_set", #TODO: Enable this when different build mode (e.g. dbg) is needed
)
load("@bazel_tools//tools/build_defs/cc:action_names.bzl", "ACTION_NAMES")

def _impl(ctx):
    #TODO: change the hard-coded bindir for MacOSX to sth smart for different platforms
    usrdir = "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr"
    bindir = "{}/bin".format(usrdir)
    tool_paths = [
        tool_path(name = "ar", path = "{}/llvm-ar".format(bindir)),
        tool_path(name = "compat-ld", path = "{}/ld".format(bindir)),
        tool_path(name = "cpp", path = "{}/clang++".format(bindir)),
        tool_path(name = "dwp", path = "{}/dwp".format(bindir)),
        tool_path(name = "gcov", path = "{}/gcov".format(bindir)),
        tool_path(name = "ld", path = "{}/lld".format(bindir)),
        tool_path(name = "nm", path = "{}/llvm-nm".format(bindir)),
        tool_path(name = "objdump", path = "{}/llvm-objdump".format(bindir)),
        tool_path(name = "strip", path = "{}/strip".format(bindir)),
        tool_path(name = "gcc", path = "{}/clang".format(bindir)),
    ]
    cxx_builtin_include_directories = [
        "{}/include".format(usrdir),
        "{}/lib/clang/11.0.0/include".format(usrdir),
        "/usr/lib/gcc/x86_64-linux-gnu",
        "/usr/include/x86_64-linux-gnu",
        "/usr/local/include",
        "/usr/include",
        "/Library/Developer/CommandLineTools/SDKs/MacOSX10.15.sdk/usr/include/",
        "/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.15.sdk/usr/include",
    ]

    #NOTE: The following actions are from tensorflow's setting. See:
    #https://github.com/tensorflow/tensorflow/blob/master/third_party/toolchains/cpus/arm/cc_config.bzl.tpl
    all_compile_actions = [
        ACTION_NAMES.c_compile,
        ACTION_NAMES.cpp_compile,
        ACTION_NAMES.linkstamp_compile,
        ACTION_NAMES.assemble,
        ACTION_NAMES.preprocess_assemble,
        ACTION_NAMES.cpp_header_parsing,
        ACTION_NAMES.cpp_module_compile,
        ACTION_NAMES.cpp_module_codegen,
        ACTION_NAMES.clif_match,
        ACTION_NAMES.lto_backend,
    ]

    all_cpp_compile_actions = [
        ACTION_NAMES.cpp_compile,
        ACTION_NAMES.linkstamp_compile,
        ACTION_NAMES.cpp_header_parsing,
        ACTION_NAMES.cpp_module_compile,
        ACTION_NAMES.cpp_module_codegen,
        ACTION_NAMES.clif_match,
    ]

    preprocessor_compile_actions = [
        ACTION_NAMES.c_compile,
        ACTION_NAMES.cpp_compile,
        ACTION_NAMES.linkstamp_compile,
        ACTION_NAMES.preprocess_assemble,
        ACTION_NAMES.cpp_header_parsing,
        ACTION_NAMES.cpp_module_compile,
        ACTION_NAMES.clif_match,
    ]

    codegen_compile_actions = [
        ACTION_NAMES.c_compile,
        ACTION_NAMES.cpp_compile,
        ACTION_NAMES.linkstamp_compile,
        ACTION_NAMES.assemble,
        ACTION_NAMES.preprocess_assemble,
        ACTION_NAMES.cpp_module_codegen,
        ACTION_NAMES.lto_backend,
    ]

    all_link_actions = [
        ACTION_NAMES.cpp_link_executable,
        ACTION_NAMES.cpp_link_dynamic_library,
        ACTION_NAMES.cpp_link_nodeps_dynamic_library,
    ]

    default_compile_flags_feature = feature(
        name = "default_compile_flags",
        enabled = True,
        flag_sets = [
            flag_set(
                actions = [
                    ACTION_NAMES.assemble,
                    ACTION_NAMES.preprocess_assemble,
                    ACTION_NAMES.linkstamp_compile,
                    ACTION_NAMES.c_compile,
                    ACTION_NAMES.cpp_compile,
                    ACTION_NAMES.cpp_header_parsing,
                    ACTION_NAMES.cpp_module_compile,
                    ACTION_NAMES.cpp_module_codegen,
                    ACTION_NAMES.lto_backend,
                    ACTION_NAMES.clif_match,
                ],
                flag_groups = [
                    flag_group(
                        flags = [
                            # opt O3
                            "-g",
                            "-DNDEBUG",
                            "-O3",
                            "-std=c++2a",
                            "-Wthread-safety",
                            "-Wno-unknown-pragmas",
                            "-Wno-inconsistent-missing-override",
                            "-Wno-deprecated-declarations",
                            "-Wno-deprecated-register",
                            "-Werror",
                            "-Wno-sign-compare",
                            "-Wno-invalid-partial-specialization",
                            "-fno-omit-frame-pointer",
                            #"-fopenmp", #TODO: On OSX with apple toolchain, this option is not supported. Resolve this
			                      "-fvisibility=hidden",
                            "-stdlib=libc++",
                            "-DC3D_STD_STRING_IMPLEMENTATION_TYPE=2",
                            "-D_FORTIFY_SOURCE=1",
                            "-DGTEST_DONT_DEFINE_FAIL=1",
                        ],
                    ),
                ],
                #with_features = [with_feature_set(features = ["opt"])],
            ),
        ],
    )

    default_linker_flags_feature = feature(
        name = "default_linker_flags",
        enabled = True,
        flag_sets = [
            flag_set(
                actions = all_link_actions,
                flag_groups = ([
                    flag_group(
                        flags = [
                            "-ldl",
                            "-lc++abi",
                            "-lc++",
                            "-lomp",
                            "-lm",
                            "-lpthread",
                            "-lrt",
                            "-fuse-ld=lld",
                            "-B/usr/bin/",
                        ],
                    ),
                ]),
            )
        ],
    )

    features = [
        default_compile_flags_feature,
        default_linker_flags_feature,
    ]

    return cc_common.create_cc_toolchain_config_info(
        ctx = ctx,
        toolchain_identifier = "k8-toolchain",
        host_system_name = "local",
        target_system_name = "local",
        target_cpu = "k8",
        target_libc = "unknown",
        compiler = "clang",
        abi_version = "local",
        abi_libc_version = "local",
        cxx_builtin_include_directories = cxx_builtin_include_directories,
        features = features,
        tool_paths = tool_paths,
    )

cc_toolchain_config =  rule(
    implementation = _impl,
    attrs = {
    #    "cpu": attr.string(mandatory=True, values=["k8"]),
    },
    provides = [CcToolchainConfigInfo],
    #executable = True,
)
