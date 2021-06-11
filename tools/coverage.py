#!/usr/bin/env python

import argparse
import glob
import os
import shutil
from contextlib import contextmanager

from invoke import task


def get_args():
    parser = argparse.ArgumentParser()
    parser.add_argument("--build", type=str, required=True, help="build-folder")
    parser.add_argument("--output", type=str, required=True, help="output folder of generated files")
    parser.add_argument("--gcov", action="store_true", required=False, help="generate gcov")
    parser.add_argument("--source-folder", type=str, required=False, help="top source folder of interest")
    return parser.parse_args()


@contextmanager
def chdir(path):
    current_path = os.getcwd()
    try:
        os.chdir(path)
        yield
    finally:
        os.chdir(current_path)


@task
def generate_gcov(c, build_folder, output_folder, top_source_folder):
    if not top_source_folder:
        raise ValueError("Source Folder needs to be set when using gcov generation.")
    text_files = glob.glob(f"{build_folder}/{top_source_folder}/**/*.gcno", recursive=True)
    shutil.rmtree(f"{output_folder}", ignore_errors=True)
    os.mkdir(f"{output_folder}")
    for file in text_files:
        filename = os.path.basename(file)
        directory = os.path.dirname(os.path.abspath(file))
        print(f"SWEET: {file}")
        with chdir(f"{output_folder}"):
            os.system(f"llvm-cov gcov {directory}/{filename}")


if __name__ == "__main__":
    args = get_args()
    if args.gcov:
        generate_gcov(None, args.build, args.output, args.source_folder)
