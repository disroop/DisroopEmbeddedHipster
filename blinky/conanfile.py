from conans import ConanFile
from conans import tools
from conan.tools.cmake import CMake, CMakeDeps
import os

class Blinky(ConanFile):
    name = "blinky"
    version = "0.1.0"
    license = "closed"
    url = "TODO"
    default_channel = "development"
    default_user = "disroop"
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps","CMakeToolchain","cmake_vars","virtualenv"
    exports_sources = "cmake/*", "source/*", "test/*", "CMakeLists.txt"

    def build_requirements(self):
        if self.settings.arch == "x86_64":
            self.build_requires("gtest/1.10.0", force_host_context=True)

    def requirements(self):
        self.requires("cmake_vars/1.0.0@disroop/development",private=True)
        if self.settings.arch == "armv7":
            self.requires("stm32_bsp_iot_node/1.1.7@disroop/development")
            self.requires("stm32_runtime_l475_vtg/0.1.0@disroop/development")

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
