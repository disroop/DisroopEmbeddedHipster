#!/usr/bin/env python

"""
The build.py is the single point containing the build logic. Thus this script can be used to build locally or
methods from the file can be used in the github actions.
The github actions shall just call methods from this file so we are not locked in the the build server solution.
"""
import os
import pathlib
import re
import shutil

import docker
from invoke import task, Collection

from tools import coverage
from tools.coverage import generate_gcov

FILE_PATH = pathlib.Path(__file__).parent.absolute()


@task(aliases=['sm'])
def setup_mumoco(c):
    c.run("mumoco --remotes")
    # c.run("export SONAR_TOKEN=who to do that??")


@task(aliases=['bb'])
def build_blinky(c):
    setup_mumoco(c)
    c.run(f"mumoco --remotes --create")


@task(aliases=['bbc'])
def build_blinky_in_container(c):
    run_in_docker("disroop/embedded-hipster:0.6.3", "invoke build-blinky")


namespace = Collection(coverage,
                       generate_gcov)


def run_docker_build(docker_image, container_command):
    current_path = os.getcwd()
    client = docker.from_env()
    container = client.containers.run(image=docker_image,
                                      command=container_command,
                                      remove=True,
                                      working_dir="/app",
                                      volumes={current_path: {'bind': '/app', 'mode': 'rw'}},
                                      detach=True)
    has_error = False
    for line in container.logs(stream=True):
        text = str(line.strip())
        print(text)
        if re.search('ERROR:', text):
            has_error = True
    if has_error:
        print(f'Failed to run container')
        exit(1)
    else:
        print("SUCCESS")


def run_in_docker(docker_image, cmd):
    bash_command = f"setup; pip3 install invoke docker;  {cmd}"
    command = f"/bin/bash -c '{bash_command}'"
    run_docker_build(docker_image, command)


@task(aliases=['c'])
def clean(c):
    folders = [".conan", "build", "cmake-build-debug"]
    for folder in folders:
        shutil.rmtree(folder, ignore_errors=True)


@task
def get_STLinkReflash():
    import requests, zipfile, StringIO
    zip_file_url = "https://www.segger.com/downloads/jlink/STLinkReflash"
    r = requests.get(zip_file_url, stream=True)
    z = zipfile.ZipFile(StringIO.StringIO(r.content))
    z.extractall()
# https://www.segger.com/downloads/jlink/STLinkReflash
