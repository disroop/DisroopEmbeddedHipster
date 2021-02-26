import os
from conans import ConanFile, tools

class ArmGCCConan(ConanFile):
    name = "armgcc_toolchain"
    version = "10.2.0"
    user = "disroop"
    channel = "release"
    settings = "os", "arch", "compiler", "build_type"

    # Implement source() and build() as usual
    def source(self):
        tools.download("https://developer.arm.com/-/media/Files/downloads/gnu-rm/10-2020q4/gcc-arm-none-eabi-10-2020-q4-major-x86_64-linux.tar.bz2?revision=ca0cbf9c-9de2-491c-ac48-898b5bbc0443&la=en&hash=68760A8AE66026BCF99F05AC017A6A50C6FD832A", "arm-gcc.tar.bz2", md5="8312c4c91799885f222f663fc81f9a31")
        self.run("mkdir toolchain && tar -xvjf arm-gcc.tar.bz2 -C toolchain --strip-components=1")
        
    def package(self):
        # Copy all the required files for your toolchain
        self.copy("*", dst="", src="toolchain")

    def package_info(self):
        bin_folder = os.path.join(self.package_folder, "bin")
        self.env_info.AR = os.path.join(bin_folder, "arm-none-eabi-ar")
        self.env_info.OBJCOPY = os.path.join(bin_folder, "arm-none-eabi-objcopy")
        self.env_info.OBJDUMP = os.path.join(bin_folder, "arm-none-eabi-objdump")
        self.env_info.SIZE = os.path.join(bin_folder, "arm-none-eabi-size")
        self.env_info.CC = os.path.join(bin_folder, "arm-none-eabi-gcc")
        self.env_info.CXX = os.path.join(bin_folder, "arm-none-eabi-g++")
        self.env_info.CONAN_CMAKE_CC = os.path.join(bin_folder, "arm-none-eabi-gcc")
        self.env_info.CONAN_CMAKE_CXX = os.path.join(bin_folder, "arm-none-eabi-g++")
        self.env_info.CONAN_CMAKE_SYSTEM_NAME = "Generic"
        self.env_info.LD =  os.path.join(bin_folder, "arm-none-eabi-ld")
        self.env_info.DEBUGGER =  os.path.join(bin_folder, "arm-none-eabi-gdb")
        self.env_info.OBJCOPY =  os.path.join(bin_folder, "arm-none-eabi-objcopy")
        self.env_info.OBJDUMP =  os.path.join(bin_folder, "arm-none-eabi-objdump")
        self.env_info.SIZE =  os.path.join(bin_folder, "arm-none-eabi-size")
        self.env_info.CPPFILT =  os.path.join(bin_folder, "arm-none-eabi-c++filt")
        self.env_info.SYSROOT = self.package_folder
        self.env_info.LDFLAGS = "-g3 -mcpu=cortex-m4 -mthumb -mabi=aapcs -mfloat-abi=hard -mfpu=fpv4-sp-d16"
        self.env_info.CFLAGS = "-mcpu=cortex-m4 -mthumb -mabi=aapcs -Wall -Werror -mfloat-abi=hard -mfpu=fpv4-sp-d16"
        self.env_info.CXXFLAGS = "-mcpu=cortex-m4 -mthumb -mabi=aapcs -Wall -Werror -mfloat-abi=hard -mfpu=fpv4-sp-d16"
        self.env_info.ASMFLAGS = "-g3 -mcpu=cortex-m4 -mthumb -mabi=aapcs -mfloat-abi=hard -mfpu=fpv4-sp-d16"
