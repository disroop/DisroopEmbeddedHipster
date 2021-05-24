#!/usr/bin/python
import os
import docker


def run_build(docker_image, container_command):
    client = docker.from_env()
    current_path = os.getcwd()
    try:
        retVal = client.containers.run(image=docker_image, command=container_command, remove=True,
                                       working_dir="/app", volumes={current_path: {'bind': '/app', 'mode': 'rw'}})
        retVal = retVal.decode('utf-8')
        print(f'{retVal}')
        print("SUCCESS")
    except docker.errors.ContainerError as exc:
        exc = exc.stderr.decode('utf-8')
        print(f'Failed to run container:')
        print(exc)
        exit(1)


if __name__ == "__main__":
    bash_command = "setup; ./buildDemo.sh"
    command = f"/bin/bash -c '{bash_command}'"
    run_build("disroop/embedded-hipster-dev:0.5.1", command)
