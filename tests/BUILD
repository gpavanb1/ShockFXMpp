# Test suite combining both test files
cc_test(
    name = "shockfxm_tests",
    srcs = [
        "test_shockfxm.cpp",
    ],
    deps = [
        "//:shockfxm_lib",
        "@splitfxmpp//:splitfxm_lib",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
        "@spdlog//:spdlog",
        "@eigen",
    ] + select({
        "//:use_cantera": ["@cantera//:cantera"],
        "//conditions:default": [],
    }),
    includes = ["include"],
    copts = [
        "-std=c++17",
        "-g",
    ] + select({
        "//:use_cantera": ["-DSPLITFXM_USE_CANTERA=1"],
        "//conditions:default": [],
    }) + select({
        "//:asan_enabled": ["-fsanitize=address", "-fno-omit-frame-pointer"],
        "//conditions:default": [],
    }),
    linkopts = ["-framework Accelerate"] + select({
        "//:asan_enabled": ["-fsanitize=address"],
        "//conditions:default": [],
    }),
    linkstatic = 1,
    timeout = "moderate",
)
