# Test suite combining both test files
cc_test(
    name = "shockfxm_tests",
    srcs = [
        "test_shockfxm.cpp",
    ],
    deps = [
        "//:shockfxm_lib",  # Your library
        "@splitfxmpp//:splitfxm_lib",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
        "@spdlog//:spdlog",    # Add spdlog dependency here as well
        "@eigen"
    ],
    includes = ["include"],  # Add this to include headers directly
    copts = [
    "-std=c++17",                   # Enable C++17
    "-g",
    "-fsanitize=address", "-fno-omit-frame-pointer",
    ],
    linkopts = ["-fsanitize=address"],
    linkstatic = 1,
    timeout = "moderate"
)
