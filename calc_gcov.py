#!/usr/bin/env python

import glob
import os
from contextlib import contextmanager
import shutil

@contextmanager
def chdir(path):
    current_path = os.getcwd()
    try:
        os.chdir(path)
        yield
    finally:
        os.chdir(current_path) 

    
if __name__ == "__main__":
    current_file = os.path.dirname(os.path.realpath(__file__))

    print(current_file)
    text_files = glob.glob(f"{current_file}/build-host/source/**/*.gcno", recursive = True)
    shutil.rmtree(f"{current_file}/build-host/gcov", ignore_errors=True)
    os.mkdir(f"{current_file}/build-host/gcov")
    with chdir(f"{current_file}/build-host/gcov"):
        for file in text_files:
            print()
            filename=os.path.basename(file)
            directory = os.path.dirname(os.path.abspath(file))
            os.system(f"llvm-cov gcov {directory}/{filename}")