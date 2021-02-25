from conans import ConanFile, CMake
import os

project_version = os.getenv("PROJECT_VERSION")
project_username = os.getenv("CONAN_USERNAME")
project_channel = os.getenv("CONAN_CHANNEL")

class Base(object):
    license = "closed"
    url = "Todo"
    default_channel = f"{project_channel}"
    default_user = f"{project_username}"
    settings = "os", "compiler", "build_type", "arch"
    generators = "cmake", "virtualenv", "env_cmake_toolchain"
    exports_sources = "src/*", "CMakeLists.txt", "test/*"
    
    def cmake_configure_build(self, cmake):
        cmake.configure()
        cmake.build()

    def run_test_analytics(self):
        if self.settings.arch == "x86_64":
            os.environ["GTEST_OUTPUT"] = f"xml:{self.build_folder}/test-report/"
            self.run("ctest --no-tests=ignore")  # cmake.test() doesn't work with parasoft cpptest
        #    if (self.settings.compiler == "parasoft-clang-wrapper") and self.options.run_cpptest_pro:
        #        self.run("cmake --build . --target parasoft-cpptest")

    def build(self):
        self.output.info("Disroop run: build")
        cmake = CMake(self)
        self.cmake_configure_build(cmake)
        self.run_test_analytics()

    def package(self):
        self.copy("include/*.h", dst="include", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)
        self.copy(f"bin/*", dst="bin", keep_path=False)
        self.copy("*", src="test-report", dst="documentation/test-reports", keep_path=True)

    def package_info(self):
        self.cpp_info.libs.append(f"{self.name}")
        
    def build_requirements(self):
        if self.settings.arch == "x86_64":
            self.build_requires("gtest/1.10.0", force_host_context=True)

    def default_requirements(self):
        #self.requires("env_cmake_toolchain/1.0.0+20210209.6@C/release")
    
    def requirements(self):
        self.default_requirements()

    def deploy(self):
        executableFolder = f"executable_{self.name}_{self.info.package_id()}"
        self.output.info(f"Deploying Artifacts to {executableFolder}")
        self.copy("*", src="bin", dst=executableFolder, keep_path=True)
        documentationFolder = f"documentation_{self.name}_{self.info.package_id()}"
        self.output.info(f"Deploying documentation for this package to {documentationFolder}")
        self.copy("*", src="documentation", dst=documentationFolder, keep_path=True)

class DisroopBase(ConanFile):
    name = "disroopBase"
    version = f"{project_version}"