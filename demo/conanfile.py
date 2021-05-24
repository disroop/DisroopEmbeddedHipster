from conans import ConanFile, CMake
import os

class DemoConan(ConanFile):
    name = "demo"
    version = "1.0"
    license = "<Put the package license here>"
    author = "<Put your name here> <And your email here>"
    url = "<Package recipe repository url here, for issues about the package>"
    description = "<Description of Demo here>"
    topics = ("<Put some tag here>", "<here>", "<and here>")
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [True, False], "sonar_scanner": [True, False]}
    default_options = {"shared": False, "fPIC": True, "sonar_scanner": False}
    generators = "cmake", "virtualenv", "cmake_paths",
    exports_sources = "src/*", "test/*", "CMakeLists.txt", "sonar-project.properties"

    def configure(self):
        del self.settings.compiler.libcxx
        del self.settings.compiler.cppstd

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
            self.run(f"sonar-scanner") 
            self.output.info("End sonar-scanner")

    def package(self):
        self.copy("*.h", dst="include", src="src")
        self.copy("*.lib", dst="lib", keep_path=False)
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.dylib*", dst="lib", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = ["demo"]
