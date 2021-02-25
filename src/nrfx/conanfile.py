from conans import ConanFile, CMake, tools


class NrfxConan(ConanFile):
    name = "nrfx"
    version = "0.1.0"
    user = "disroop"
    channel = "develop"
    license = "<Put the package license here>"
    author = "<Put your name here> <And your email here>"
    url = "<Package recipe repository url here, for issues about the package>"
    description = "<Description of Nrfx here>"
    topics = ("<Put some tag here>", "<here>", "<and here>")
    settings = "os", "compiler", "build_type", "arch"
    exports_sources = "CMakeLists.txt"

    def source(self):
        git = tools.Git(folder=self.source_folder+"/nrfx")
        git.clone("https://github.com/NordicSemiconductor/nrfx.git",branch="master", shallow=True)
        git_cmsis = tools.Git(folder=self.source_folder+"/cmsis")
        git_cmsis.clone("https://github.com/ARM-software/CMSIS_5.git",branch="5.7.0", shallow=True)

    def build(self):
        cmake = CMake(self)
        cmake.definitions["CMAKE_TRY_COMPILE_TARGET_TYPE"]="STATIC_LIBRARY"
        cmake.definitions["CMAKE_CXX_FLAGS"]="-mcpu=cortex-m4 -mthumb -mabi=aapcs --std=gnu99"
        cmake.definitions["CMAKE_C_FLAGS"]="-mcpu=cortex-m4 -mthumb -mabi=aapcs --std=gnu99"
        cmake.configure()
        cmake.build()

    def package(self):
        self.copy("*.a","lib",keep_path=False)
        self.copy("*.h","include",keep_path=True, excludes="nrfx/doc")


