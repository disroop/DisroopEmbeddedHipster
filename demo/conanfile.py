from conans import ConanFile, CMake
import os

from conans.client import build

class DemoConan(ConanFile):
    name = "demo"
    version = "1.0"
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [True, False], "sonar_scanner": [True, False]}
    default_options = {"shared": False, "fPIC": True, "sonar_scanner": False}
    generators = "cmake_paths", "CMakeDeps","CMakeToolchain","virtualenv" , "cmake_vars"
    exports_sources = "src/*", "test/*", "CMakeLists.txt", "sonar-project.properties"

    def configure(self):
        del self.settings.compiler.libcxx
        del self.settings.compiler.cppstd


    def requirements(self):
        self.requires("cmake_vars/1.0.0@disroop/development",private=True)

    def build_requirements(self):
        if self.settings.arch == "x86_64":
           self.build_requires("gtest/1.10.0", force_host_context=True)
        

    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        self.run(f"build-wrapper --out-dir bw-output cmake --build .")
        if self.options.sonar_scanner == True:
            self.output.info("Start sonar-scanner")
            self.run(f"sonar-scanner -Dsonar.login={os.environ['SONAR_TOKEN']}") 
            self.output.info("End sonar-scanner")
        else:
            cmake.build()
        cmake.test()            
        
        


    def package(self):
        self.copy("*.h", dst="include", src="src")
        self.copy("*.lib", dst="lib", keep_path=False)
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.dylib*", dst="lib", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = ["demo"]
