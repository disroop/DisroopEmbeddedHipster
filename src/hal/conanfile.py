import os
from conans import ConanFile, CMake
from dotenv import load_dotenv
from pathlib import Path

def loadDevEnv():
    current_path = os.getcwd()
    env_path = f'{current_path}/../../.env/dev.env'
    if os.path.exists(env_path):
        load_dotenv(dotenv_path=env_path)
    project_version = os.getenv("PACKAGE_VERSION")


project_version = os.getenv("PACKAGE_VERSION")
if not project_version:
    loadDevEnv()
    
class Hal(ConanFile):
    name = "hal"
    version=f'{project_version}'
    url = "todo add url"
    license = "Closed"
    description = "TODO"
    generators = "cmake", "cmake_paths","virtualenv", "txt"
    settings = "os", "compiler", "build_type", "arch"
    exports_sources = "CMakeLists.txt",  "include/*", "src/*", "test/*", ".parasoft_settings/*"
    
    def requirements(self):
        if self.settings.arch == "armv7":
            self.requires(f"nrfx/0.1.0@disroop/develop")
        elif self.settings.arch == "x86_64":
            self.requires("gtest/1.10.0", private=True)
        else:
             raise ConanInvalidConfiguration("unsupported arch")         

    def package_info(self):
        self.cpp_info.libs = ["halnrf"]
        self.cpp_info.srcdirs = ["src"]
    
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
        self.copy("include/*.hpp", dst="include", keep_path=False)


        



        
