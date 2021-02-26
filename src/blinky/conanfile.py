import os
from conans import ConanFile, CMake
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
    
class BlinkyLc(ConanFile):
    name = "blinky"
    version=f'{project_version}'
    user = "disroop"
    channel = "develop"
    url = "todo add url"
    license = "Closed"
    description = "TODO"
    generators = "cmake", "cmake_paths","virtualenv", "txt"
    settings = "os", "compiler", "build_type", "arch"
    exports_sources = "CMakeLists.txt",  "src/*", "test/*",

    def requirements(self):
        self.requires(f"hal/{project_version}@disroop/develop")        

    def package_info(self):
        self.cpp_info.srcdirs = ["src"]
    
    def disroop_configure(self,cmake):
        if os.getenv("DISROOP_CMAKE_TRY_COMPILE_TARGET_TYPE"):
            cmake.definitions["CMAKE_TRY_COMPILE_TARGET_TYPE"] = os.getenv("DISROOP_CMAKE_TRY_COMPILE_TARGET_TYPE")
        cmake.definitions["CMAKE_EXPORT_COMPILE_COMMANDS"] = 1

    def build(self):
        cmake = CMake(self, set_cmake_flags=True)
        self.disroop_configure(cmake)
        cmake.configure()
        cmake.build()

    def package(self):
        if self.settings.arch == "armv7":
            self.copy("**/blinky_app", dst="bin", keep_path=False)
            self.copy("**/blinky_app.bin", dst="bin", keep_path=False)
            self.copy("**/blinky_app.dump", dst="bin", keep_path=False)
            self.copy("**/blinky_app.hex", dst="bin", keep_path=False)
        elif self.settings.arch == "x86_64":
            self.copy("**/reports/*", dst="reports", keep_path=True)


        
