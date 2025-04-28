from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, CMakeDeps


class MarLibConan(ConanFile):
    name = "libmar"
    version = "0.1"
    settings = ["os", "compiler", "build_type", "arch"]
    options = {
        "build_tests": [True, False],
    }
    default_options = {
        "build_tests": True,
    }
    generators = []
    requires = ["glfw/3.4"]
    test_requires = ["gtest/1.16.0"]

    def layout(self):
        self.folders.build = "build"
        self.folders.generators = "build"

    def generate(self):
        tc = CMakeToolchain(self)
        tc.cache_variables["CMAKE_EXPORT_COMPILE_COMMANDS"] = True
        # pass our build_tests option into CMake
        tc.cache_variables["BUILD_TESTS"] = self.options.build_tests  # type: ignore[reportAttributeAccessIssue]
        tc.generate()
        deps = CMakeDeps(self)
        deps.build_context_activated = ["gtest"]
        deps.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
        # only run tests if BUILD_TESTS is true
        if self.options.build_tests:  # type: ignore[reportAttributeAccessIssue]
            cmake.test()
