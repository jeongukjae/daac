package(default_visibility = ["//visibility:public"])

cc_library(
    name = "darts_clone_builder",
    srcs = ["darts_clone_builder.cc"],
    hdrs = ["darts_clone_builder.h"],
    deps = [
        "@com_google_absl//absl/container:flat_hash_set",
        "@com_google_absl//absl/status:statusor",
        "@darts_clone",
        ":darts_clone_wrapper",
    ],
)

cc_library(
    name = "darts_clone_wrapper",
    hdrs = ["darts_clone_wrapper.h"],
    deps = ["@com_google_absl//absl/status:statusor"],
)

cc_library(
    name = "daac",
    hdrs = ["daac.h"],
    deps = [
        "@com_google_absl//absl/status:statusor",
        ":darts_clone_wrapper",
    ],
)

cc_test(
    name = "daac_test",
    srcs = ["daac_test.cc"],
    deps = [
        ":daac",
        ":darts_clone_builder",
        "@com_google_googletest//:gtest_main",
    ],
)
