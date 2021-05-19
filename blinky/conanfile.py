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
    default_user = "mymichu"
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps","CMakeToolchain","cmake_vars","virtualenv"
    exports_sources = "source/*", "CMakeLists.txt"
    
    def requirements(self):
        self.requires(f"stm32_bsp_iot_node/1.1.7@disroop/development")
        self.requires(f"cmake_vars/1.0.0@disroop/development",private=True)

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
    
    def package(self):
        self.package("*.hex",src="source",dst="bin")
        self.package("*.bin",src="source",dst="bin")
        self.package("*.elf",src="source",dst="bin")
        self.package("*.map",src="source",dst="bin")

