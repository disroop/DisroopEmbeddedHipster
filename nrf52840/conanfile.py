import os
from conans import ConanFile, CMake
from dotenv import load_dotenv
from pathlib import Path

def loadDevEnv():
    current_path = os.getcwd()
    env_path = f'{current_path}/../.env/dev.env'
    if os.path.exists(env_path):
        load_dotenv(dotenv_path=env_path)
    project_version = os.getenv("PACKAGE_VERSION")


project_version = os.getenv("PACKAGE_VERSION")
if not project_version:
    loadDevEnv()

class PlatformNrf52840(ConanFile):
    name = "platformnrf52840"
    url = "todo add url"
    version=f'{project_version}'
    license = "Closed"
    description = "TODO"
    generators = "cmake", "virtualenv", "txt", "cmake_find_package"
    settings = "build_type", "os", "arch"
    exports_sources = "CMakeLists.txt", "cmake/*", "nrf52dk/*"
    keep_imports = True

    #def generate(self):
    #    tc = CMakeToolchain(self)
    #    tc.preprocessor_definitions["MYVAR"] = "MyValue"
    #    # customize toolchain "tc"
    #    tc.generate()

    def requirements(self):
        self.requires(f"nrf5sdk/{project_version}@disroop/development")

    
    def disroop_configure(self, cmake):
        if os.getenv("DISROOP_CMAKE_TRY_COMPILE_TARGET_TYPE"):
            cmake.definitions["CMAKE_TRY_COMPILE_TARGET_TYPE"] = os.getenv("DISROOP_CMAKE_TRY_COMPILE_TARGET_TYPE")
        cmake.definitions["CMAKE_EXPORT_COMPILE_COMMANDS"] = 1
        cmake.definitions["DISROOP_BOARD"] = self.settings.os.board

    def imports(self):
        self.copy("nrf5sdk/config/nrf52840/config/*", dst="", root_package="nrf5sdk", folder=True,keep_path=True)
        self.copy("nrf5sdk/components/*"            , dst="", root_package="nrf5sdk", folder=True,keep_path=True)
        self.copy("nrf5sdk/external/*"              , dst="", root_package="nrf5sdk", folder=True,keep_path=True)
        self.copy("nrf5sdk/integration/*"           , dst="", root_package="nrf5sdk", folder=True,keep_path=True)
        self.copy("nrf5sdk/modules/*"               , dst="", root_package="nrf5sdk", folder=True,keep_path=True)

    def package_info(self):
        self.cpp_info.defines = ["BOARD_PCA10056"]
        self.cpp_info.defines = ["USE_APP_CONFIG"]
        self.cpp_info.defines = ["NRF52840_XXAA"]
        self.cpp_info.srcdirs = ["src"]
        self.cpp_info.libs = ["platform-nrf52840"]
        self.cpp_info.builddirs.append("cmake")
        if self.settings.os.board == "NRF52_DK":
            self.cpp_info.builddirs.append("nrf52dk/cmake")

    def build(self):
        cmake = CMake(self)
        self.disroop_configure(cmake)
        cmake.configure()
        cmake.build()

    def package(self):
        self.copy("cmake/*", dst="cmake", keep_path=False)
        self.copy("**/nrf5sdk/components/boards/*.h", dst="include", keep_path=False)
        self.copy("**/nrf5sdk/components/libraries/delay/nrf_delay.h", dst="include", keep_path=False)
        self.copy("**/nrf5sdk/components/libraries/util/*.h", dst="include", keep_path=False)
        self.copy("**/nrf5sdk/components/toolchain/cmsis/include/*.h", dst="include", keep_path=False)
        self.copy("**/nrf5sdk/components/drivers_nrf/nrf_soc_nosd/*.h", dst="include", keep_path=False)
        self.copy("**/nrf5sdk/modules/nrfx/*.h",dst="include", keep_path=False)
        self.copy("**/nrf5sdk/modules/nrfx/soc/*.h",dst="include/soc", keep_path=False)
        self.copy("**/nrf5sdk/integration/nrfx/*.h",dst="include", keep_path=False)
        self.copy("**/nrf5sdk/integration/nrfx/legacy/*.h",dst="include/legacy", keep_path=False)
        self.copy("**/nrf5sdk/config/nrf52840/config/sdk_config.h",dst="include", keep_path=False)
        self.copy("**/nrf5sdk/modules/nrfx/drivers/*.h",dst="include/drivers", keep_path=False)
        self.copy("**/nrf5sdk/modules/nrfx/mdk/*.h",dst="include", keep_path=False)
        self.copy("**/nrf5sdk/modules/nrfx/mdk/*.ld",dst="include", keep_path=False)
        self.copy("**/libplatform-nrf52840.a", dst="lib", keep_path=False)
        if self.settings.os.board == "NRF52_DK":
            self.copy("nrf52dk/config/*.h", dst="include", keep_path=False)
            self.copy("nrf52dk/cmake/*", dst="nrf52dk/cmake", keep_path=False)
            self.copy("nrf52dk/linker/*.ld", dst="nrf52dk/linker", keep_path=False)
        elif self.settings.os.board == "YP_UNO_PEN_LC":
            #TODO: set export files for YP_UNO_PEN_LC BOARD
            pass
        else:
            raise ConanInvalidConfiguration("This board is not supported")
