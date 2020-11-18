import os
from conans import ConanFile, CMake
from conans.tools import download, unzip
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

    def downloadArtefact(self, url):
        artefact_zip = "nrf5sdk.zip"
        download(f"{url}", f"{artefact_zip}")
        unzip(artefact_zip, "nrf5sdk")
        os.unlink(artefact_zip)

    def source(self):
        self.downloadArtefact("https://www.nordicsemi.com/-/media/Software-and-other-downloads/SDKs/nRF5/Binaries/nRF5SDK160098a08e2.zip")

    def build(self):
        pass

    def package(self):
        self.copy("*.h", keep_path=True)
        self.copy("*.c", keep_path=True)
        self.copy("*.S", keep_path=True)
        self.copy("*.ld", keep_path=True)
        self.copy("*.a", keep_path=True)

