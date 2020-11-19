import os
import argparse
from contextlib import contextmanager
from pathlib import Path
import shutil
from dotenv import load_dotenv

def loadDevEnv():
    current_path = os.getcwd()
    env_path = f'{current_path}/.env/dev.env'
    if os.path.exists(env_path):
        load_dotenv(dotenv_path=env_path)
    return os.getenv("PACKAGE_VERSION")

def get_args():
    parser = argparse.ArgumentParser()
    parser.add_argument("--version", type=str, required=False, help="Package Version Number")
    return parser.parse_args()

def run(cmd, assert_error=False):
    print("*********** Running: %s" % cmd)
    ret = os.system(cmd)
    if ret == 0 and assert_error:
        raise Exception("Command unexpectedly succedeed: %s" % cmd)
    if ret != 0 and not assert_error:
        raise Exception("Failed command: %s" % cmd)

@contextmanager
def chdir(path):
    current_path = os.getcwd()
    try:
        os.chdir(path)
        yield
    finally:
        os.chdir(current_path)

def conan_create_packages(version):
    with chdir(os.path.dirname(os.path.realpath(__file__))):
        run(f'conan export nrf52840/conanfile.py {version}@disroop/development')
        run(f'conan export nrf5sdk/conanfile.py {version}@disroop/development')
        run(f'conan export hal/conanfile.py {version}@disroop/development')
        run(f'conan export blinky/conanfile.py {version}@disroop/development')

        #run(f'conan create -pr clang-linux-debug --build=missing blinky/conanfile.py {version}@disroop/development')
        run(f'conan create -pr gcc-nrf52840-debug --build=missing --settings os.board=NRF52_DK blinky/conanfile.py {version}@disroop/development')
        
if __name__ == "__main__":
    args = get_args()

    if args.version :
        os.environ['PACKAGE_VERSION'] = args.version

    project_version = os.getenv("PACKAGE_VERSION")
    if not project_version:
         project_version = loadDevEnv()

    conan_create_packages(project_version)