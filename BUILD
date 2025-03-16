# Main executable
cc_binary(
    name = "main",
    srcs = ["main.cpp"],
    deps = [
        ":shockfxm_lib",
        "@spdlog//:spdlog",  # Add spdlog dependency here as well
        "@eigen",
    ],
    includes = ["include"],  # Add this to include headers directly
    copts = ["-std=c++17",],  # Enable C++17
)

# Library definition
cc_library(
    name = "shockfxm_lib",
    hdrs = glob([
        "include/**/*.h",  # Header files in include/
    ]),
    srcs = glob([
        "src/**/*.cpp",  # Source files in src/
    ]),
    visibility = ["//visibility:public"],
    deps = [
        "@splitfxmpp//:splitfxm_lib",
        "@spdlog//:spdlog",  # Add spdlog dependency here as well
        "@eigen",
    ],
    includes = ["include"],  # Add this to include headers directly
    copts = ["-std=c++17",],  # Enable C++17
)
