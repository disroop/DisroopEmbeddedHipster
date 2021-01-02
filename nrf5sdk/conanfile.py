import os
from conans import ConanFile, CMake
from conans.tools import download, unzip, Git, patch, replace_in_file

from dotenv import load_dotenv
from pathlib import Path

def loadDevEnv():
    current_path = os.getcwd()
    env_path = f'{current_path}/../.env/dev.env'
    if os.path.exists(env_path):
        load_dotenv(dotenv_path=env_path)
    return os.getenv("PACKAGE_VERSION")

project_version = os.getenv("PACKAGE_VERSION")
if not project_version:
    project_version = loadDevEnv()

class NRF5SDKConan(ConanFile):
    name = "nrf5sdk"
    version=f'{project_version}'
    settings = "os", "compiler", "build_type", "arch"
    description = "<Description of nrf5sdk here>"
    url = "None"
    license = "None"
    author = "None"
    topics = None
    exports_sources = "*.patch"

    def downloadArtefact(self, url):
        artefact_zip = "nrf5sdk.zip"
        download(f"{url}", f"{artefact_zip}")
        unzip(artefact_zip, "nrf5sdk")
        os.unlink(artefact_zip)

    def source(self):
        self.downloadArtefact("https://www.nordicsemi.com/-/media/Software-and-other-downloads/SDKs/nRF5/Binaries/nRF5SDK160098a08e2.zip")
        git = Git("cmake-nrf")
        git.clone("https://github.com/Polidea/cmake-nRF5x.git",branch="master",shallow=True)

    def disroop_configure(self,cmake):
        if os.getenv("DISROOP_CMAKE_TRY_COMPILE_TARGET_TYPE"):
            cmake.definitions["CMAKE_TRY_COMPILE_TARGET_TYPE"] = os.getenv("DISROOP_CMAKE_TRY_COMPILE_TARGET_TYPE")
        cmake.definitions["CMAKE_EXPORT_COMPILE_COMMANDS"] = 1
        #cmake.definitions["CMAKE_TOOLCHAIN_FILE"]=os.path.join(self.source_folder, "nrf5sdk/cmake/arm-none-eabi.cmake")
        #cmake.definitions["TOOLCHAIN_PREFIX"]=os.path.join(self.source_folder, "nrf5sdk/cmake/arm-none-eabi.cmake")
        #-DTOOLCHAIN_PREFIX="/Users/przemyslawlenart/git/nrf5-cmake/ci/toolchains/gcc" \
        cmake.definitions["NRF5_SDK_PATH"]=os.path.join(self.source_folder, "nrf5sdk")
        cmake.definitions["NRF5_SDK_VERSION"]="16.0.0"
        cmake.definitions["NRF5_BOARD"]="pca10056"
        cmake.definitions["NRF5_SOFTDEVICE_VARIANT"]="s140"
        cmake.definitions["NRF5_LINKER_SCRIPT"]="/workspace/nrf5sdk/source/nrf5sdk/config/nrf52840/armgcc/generic_gcc_nrf52.ld"

    def build(self):
        replace_in_file(f"{self.source_folder}/patch/nrf5.patch", "REPLACE_SDK_IN_SOURCE_DIR",
        f"{self.source_folder}/nrf5sdk")
        patch(base_path=f"{self.source_folder}/cmake-nrf",patch_file=f"{self.source_folder}/patch/nrf5.patch")
#

    def package(self):
        self.copy("*.cmake", keep_path=False)

    def package_info(self):
        self.cpp_info.build_modules.append("nrf5.cmake")