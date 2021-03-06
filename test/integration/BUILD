licenses(["notice"])  # Apache 2

load("@rules_python//python:defs.bzl", "py_binary", "py_library")
load(
    "@envoy//bazel:envoy_build_system.bzl",
    "envoy_package",
)
load("@python_pip_deps//:requirements.bzl", "requirement")

envoy_package()

py_library(
    name = "integration_test_base",
    srcs = [
        "common.py",
        "integration_test_fixtures.py",
        "nighthawk_grpc_service.py",
        "nighthawk_test_server.py",
        "utility.py",
    ],
    data = [
        "configurations/nighthawk_http_origin.yaml",
        "configurations/nighthawk_https_origin.yaml",
        "configurations/sni_origin.yaml",
        "//:nighthawk_client",
        "//:nighthawk_service",
        "//:nighthawk_test_server",
        "@envoy//test/config/integration/certs",
    ],
    deps = [
        requirement("requests"),
        # The following are implied by 'request'.
        requirement("urllib3"),
        requirement("chardet"),
        requirement("certifi"),
        requirement("idna"),
        requirement("pytest"),
        requirement("pytest-dependency"),
        # The following are implied by pytest & co.
        requirement("attrs"),
        requirement("pluggy"),
        requirement("zipp"),
        requirement("six"),
        requirement("atomicwrites"),
        requirement("py"),
        requirement("more_itertools"),
        requirement("importlib_metadata"),
        requirement("pathlib2"),
        requirement("packaging"),
        requirement("pytest-xdist"),
        requirement("execnet"),
        requirement("apipkg"),
    ],
)

py_library(
    name = "test_integration_basics_lib",
    srcs = ["test_integration_basics.py"],
    deps = [":integration_test_base"],
)

py_library(
    name = "test_connection_management_lib",
    srcs = ["test_connection_management.py"],
    deps = [":integration_test_base"],
)

py_library(
    name = "test_integration_zipkin_lib",
    srcs = ["test_integration_zipkin.py"],
    deps = [":integration_test_base"],
)

py_library(
    name = "test_grpc_service_lib",
    srcs = ["test_grpc_service.py"],
    deps = [":integration_test_base"],
)

py_library(
    name = "test_remote_execution_lib",
    srcs = ["test_remote_execution.py"],
    deps = [":integration_test_base"],
)

py_binary(
    name = "integration_test",
    srcs = ["integration_test.py"],
    args = select({
        "//bazel:zipkin_disabled": [
            "\"not zipkin\"",
        ],
        "//conditions:default": [],
    }),
    python_version = "PY3",
    srcs_version = "PY3ONLY",
    deps = [
        ":test_connection_management_lib",
        ":test_grpc_service_lib",
        ":test_integration_basics_lib",
        ":test_integration_zipkin_lib",
        ":test_remote_execution_lib",
    ],
)
