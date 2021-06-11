#!/usr/bin/python
import argparse
import os

import docker


def get_args():
    parser = argparse.ArgumentParser()
    parser.add_argument("--sonartoken", type=str, required=False, default="", help="Use Sonartoken")
    return parser.parse_args()


def run_build(docker_image, container_command, sonar_token):
    client = docker.from_env()
    current_path = os.getcwd()
    try:
        retVal = client.containers.run(image=docker_image, command=container_command, remove=True,
                                       working_dir="/app", volumes={current_path: {'bind': '/app', 'mode': 'rw'}},
                                       environment=[f"SONAR_TOKEN={sonar_token}"])
        retVal = retVal.decode('utf-8')
        print(f'{retVal}')
        print("SUCCESS")
    except docker.errors.ContainerError as exc:
        exc = exc.stderr.decode('utf-8')
        print(f'Failed to run container:')
        print(exc)
        exit(1)


def container_demo_build():
    args = get_args()
    bash_command = "setup; ./buildDemo.sh"
    command = f"/bin/bash -c '{bash_command}'"
    run_build("disroop/embedded-hipster-sonar:0.6.2", command, args.sonartoken)


if __name__ == "__main__":
    container_demo_build()
