from conans import ConanFile
from conans import tools
from conan.tools.cmake import CMake, CMakeDeps, CMakeToolchain
import os

class Blinky(ConanFile):
    name = "blinky"
    version = "0.1.0"
    license = "closed"
    url = "TODO"
    description = "a blinky example"
    channel = "development"
    user = "disroop"
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain", "virtualenv"
    exports_sources = "cmake/*", "source/*", "test/*", "CMakeLists.txt"

    def generate(self):
        tc = CMakeToolchain(self)
        if self.settings.arch == "armv7":
            tc.variables["CMAKE_TRY_COMPILE_TARGET_TYPE"] = "STATIC_LIBRARY"
            tc.variables["CMAKE_SYSTEM_NAME"] = "Generic"
        tc.generate()

    def build_requirements(self):
        if self.settings.arch == "x86_64":
            self.build_requires("gtest/1.10.0", force_host_context=True)

    def requirements(self):
        if self.settings.arch == "armv7":
            self.requires("stm32_bsp_iot_node/1.1.7@disroop/development")
            self.requires("stm32_runtime_l475_vtg/0.1.0@disroop/development")
        elif self.settings.arch == "x86_64":
            self.requires("abseil/20210324.2")

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
        if self.settings.arch == "x86_64":
            cmake.test()
    
    def package(self):
        self.copy("blinky.hex",src=f"{self.build_folder}/bin",dst="bin")
        self.copy("blinky.bin",src=f"{self.build_folder}/bin",dst="bin")
        self.copy("blinky",src=f"{self.build_folder}/bin",dst="bin")
        self.copy("flash.jLink",src=f"{self.build_folder}/bin",dst="bin")
        self.copy("blinky.map",src=f"{self.build_folder}/bin",dst="bin")
