import os

from conans import ConanFile, CMake


class Blinky(ConanFile):
    name = "blinky"
    version = "0.1"
    url = "todo add url"
    license = "Closed"
    description = "TODO"
    generators = "cmake", "cmake_paths","virtualenv", "txt"
    settings = "build_type", "os", "arch"
    exports_sources = "CMakeLists.txt",  "src/*"
    keep_imports = True

    def package_info(self):
        self.cpp_info.srcdirs = ["src"]
        
    def build(self):
        cmake = CMake(self, set_cmake_flags=True)
        if os.getenv("DISROOP_CMAKE_TRY_COMPILE_TARGET_TYPE"):
            cmake.definitions["CMAKE_TRY_COMPILE_TARGET_TYPE"] = os.getenv("DISROOP_CMAKE_TRY_COMPILE_TARGET_TYPE")
        cmake.definitions["CMAKE_EXPORT_COMPILE_COMMANDS"] = 1
        cmake.configure()
        cmake.build()

    def test(self):
        pass
