# Configuration for Cantera support
config_setting(
    name = "use_cantera",
    values = {"define": "SPLITFXM_USE_CANTERA=true"},
)

# Configuration for Address Sanitizer
config_setting(
    name = "asan_enabled",
    values = {"define": "asan=true"},
)

# Shared compiler options
_COMMON_COPTS = ["-std=c++17"] + select({
    ":use_cantera": ["-DSPLITFXM_USE_CANTERA=1"],
    "//conditions:default": [],
})

# Main executable
cc_binary(
    name = "main",
    srcs = ["main.cpp"],
    deps = [
        ":shockfxm_lib",
        "@spdlog//:spdlog",
        "@eigen",
    ] + select({
        ":use_cantera": ["@cantera//:cantera"],
        "//conditions:default": [],
    }),
    includes = ["include"],
    copts = _COMMON_COPTS + select({
        ":asan_enabled": ["-fsanitize=address", "-fno-omit-frame-pointer"],
        "//conditions:default": [],
    }),
    linkopts = ["-framework Accelerate"] + select({
        ":asan_enabled": ["-fsanitize=address"],
        "//conditions:default": [],
    }),
)

# Library definition
cc_library(
    name = "shockfxm_lib",
    hdrs = glob(["include/**/*.h"]),
    srcs = glob(["src/**/*.cpp"]),
    visibility = ["//visibility:public"],
    deps = [
        "@splitfxmpp//:splitfxm_lib",
        "@spdlog//:spdlog",
        "@eigen",
    ] + select({
        ":use_cantera": ["@cantera//:cantera"],
        "//conditions:default": [],
    }),
    includes = ["include"],
    copts = _COMMON_COPTS + select({
        ":asan_enabled": ["-fsanitize=address", "-fno-omit-frame-pointer"],
        "//conditions:default": [],
    }),
    linkopts = ["-framework Accelerate"] + select({
        ":asan_enabled": ["-fsanitize=address"],
        "//conditions:default": [],
    }),
)
