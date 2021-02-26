import os
from conans import ConanFile, CMake
from dotenv import load_dotenv
from pathlib import Path
from conans.tools import download, unzip

def loadDevEnv():
    current_path = os.getcwd()
    env_path = f'{current_path}/../../../.env/dev.env'
    if os.path.exists(env_path):
        load_dotenv(dotenv_path=env_path)
    project_version = os.getenv("PACKAGE_VERSION")


project_version = os.getenv("PACKAGE_VERSION")
if not project_version:
    loadDevEnv()
    
class nrfsdk(ConanFile):
    name = "nrfsdk"
    version = "0.1.0"
    user = "disroop"
    channel = "develop"
    url = "todo add url"
    license = "Closed"
    description = "TODO"
    generators = "cmake", "cmake_paths","virtualenv", "txt"
    settings = "os", "compiler", "build_type", "arch"
    exports_sources = "CMakeLists.txt",  "linker/*", "src/*", "config/*", "cmake/*"
    
    def requirements(self):
        if self.settings.arch == "armv7":
            self.requires(f"nrfx/0.1.0@disroop/develop")       

    def package_info(self):
        self.cpp_info.libs = [f"{self.name}"]
        self.cpp_info.srcdirs = ["src"]
        self.cpp_info.defines.append("BOARD_D52DK1")
    
    def disroop_configure(self,cmake):
        cmake.definitions["CMAKE_TRY_COMPILE_TARGET_TYPE"]="STATIC_LIBRARY"
        cmake.definitions["CMAKE_EXPORT_COMPILE_COMMANDS"] = 1

    def build(self):
        cmake = CMake(self, set_cmake_flags=True)
        self.disroop_configure(cmake)
        cmake.configure()
        cmake.build()
        

    def package(self):
        self.copy("*.a", dst="lib", keep_path=False)
        self.copy("*.h", src="nrf5sdk/components/boards", dst="include", keep_path=False)
        self.copy("*.h", src="nrf5sdk/components/libraries/util", dst="include", keep_path=False)
        self.copy("*.h", src="nrf5sdk/components/libraries/delay", dst="include", keep_path=False)
        self.copy("*.h", src="nrf5sdk/components/toolchain/cmsis/include/", dst="include", keep_path=False)
        self.copy("*.h", src="nrf5sdk/components/drivers_nrf/nrf_soc_nosd/", dst="include", keep_path=False)
        self.copy("*.h", src="nrf5sdk/modules/nrfx/", dst="include", keep_path=False)
        self.copy("*.h", src="nrf5sdk/modules/nrfx/soc/", dst="include/soc", keep_path=False)
        self.copy("*.h", src="nrf5sdk/integration/nrfx/", dst="include", keep_path=False)
        self.copy("*.h", src="nrf5sdk/integration/nrfx/legacy/", dst="include/legacy", keep_path=False)
        self.copy("*.h", src="nrf5sdk/modules/nrfx/mdk/", dst="include", keep_path=False)
        #NRF52840
        self.copy("*.h",    src="nrf5sdk/config/nrf52840/config/", dst="include", keep_path=False)
        self.copy("app_config.h", src="config", dst="include", keep_path=False)
        self.copy("*.cmake", src="cmake", dst="cmake", keep_path=False)
        self.copy("*.ld",  src="linker",dst="linker", keep_path=False)


    def downloadArtefact(self, url):
        artefact_zip = "nrf5sdk.zip"
        download(f"{url}", f"{artefact_zip}")
        unzip(artefact_zip, "nrf5sdk")
        os.unlink(artefact_zip)

    def deploy(self):
        # deploy the documentation when conan installing to make it easily available
        svdFolder = f"svd"
        self.output.info(f"Deploying svd for this package to {svdFolder}")
        self.copy("nrf52840.svd", src="nrf5sdk/modules/nrfx/mdk", dst=svdFolder, keep_path=False)

    def source(self):
        self.downloadArtefact("https://www.nordicsemi.com/-/media/Software-and-other-downloads/SDKs/nRF5/Binaries/nRF5SDK160098a08e2.zip")


        
