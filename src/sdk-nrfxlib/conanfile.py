from conans import ConanFile, CMake, tools


class NrfxConan(ConanFile):
    name = "nrfx"
    version = "0.1.0"
    license = "<Put the package license here>"
    author = "<Put your name here> <And your email here>"
    url = "<Package recipe repository url here, for issues about the package>"
    description = "<Description of Nrfx here>"
    topics = ("<Put some tag here>", "<here>", "<and here>")
    settings = "os", "compiler", "build_type", "arch"
    exports_sources = "CMakeLists.txt"
    build_requires= "armgcc_toolchain/10.2.0@disroop/release"

    def source(self):
        git = tools.Git(folder=self.source_folder+"/nrfxlib")
        git.clone("https://github.com/nrfconnect/sdk-nrfxlib.git",branch="master", shallow=True)

    def build(self):
        pass
    
    def package(self):
        self.copy("*.a","lib",keep_path=False)
        self.copy("*.h","include",keep_path=True, excludes="nrfx/doc")


    def package_info(self):
        self.cpp_info.libs = ["mdk","soc","drivers"]


