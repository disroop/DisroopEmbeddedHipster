import os
from conans import ConanFile, CMake
from conans.tools import download, unzip, Git
from dotenv import load_dotenv
from pathlib import Path

class NRF5SDKConanTest(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    description = "<Description of nrf5sdk here>"
    url = "None"
    license = "None"
    author = "None"
    topics = None
    generators = "cmake_find_package", "cmake"
    exports = "*.c", "CMakeLists.txt"

    def disroop_configure(self,cmake):
        if os.getenv("DISROOP_CMAKE_TRY_COMPILE_TARGET_TYPE"):
            cmake.definitions["CMAKE_TRY_COMPILE_TARGET_TYPE"] = os.getenv("DISROOP_CMAKE_TRY_COMPILE_TARGET_TYPE")
        cmake.definitions["CMAKE_EXPORT_COMPILE_COMMANDS"] = 1
        cmake.definitions["NRF5_BOARD"]="pca10056"
        cmake.definitions["NRF5_TARGET"]="nrf52840_xxaa"
        cmake.definitions["NRF5_SOFTDEVICE_VARIANT"]="s140"
        #cmake.definitions["NRF5_LINKER_SCRIPT"]="/workspace/nrf5sdk/source/nrf5sdk/config/nrf52840/armgcc/generic_gcc_nrf52.ld"

    def build(self):
        cmake = CMake(self)
        self.disroop_configure(cmake)
        cmake.configure()
        cmake.build()

    def test(self):
        elf_path = os.path.join(self.build_folder, "blinky")
        bin_path = os.path.join(self.build_folder, "blinky.bin")
        hex_path = os.path.join(self.build_folder, "blinky.hex")
        assert(os.path.isfile(elf_path))
        assert(os.path.isfile(bin_path))
        assert(os.path.isfile(hex_path))
