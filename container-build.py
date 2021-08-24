#!/usr/bin/python
import os
import docker
import re


def run_build(docker_image, container_command):
    client = docker.from_env()
    current_path = os.getcwd()

    client = docker.from_env()
    container = client.containers.run(image=docker_image, command=container_command, remove=True,
                                      working_dir="/app", volumes={current_path: {'bind': '/app', 'mode': 'rw'}}, detach=True)
    hasError = False
    for line in container.logs(stream=True):
        text = str(line.strip())
        print(text)
        if re.search('ERROR:', text):
            hasError = True
    if hasError:
        print(f'Failed to run container')
        exit(1)
    else:
        print("SUCCESS")


if __name__ == "__main__":
    bash_command = "setup; ./build.sh"
    command = f"/bin/bash -c '{bash_command}'"
    run_build("disroop/embedded-hipster:0.6.9", command)
