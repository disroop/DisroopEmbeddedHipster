import pathlib

from invoke import task

import tasks.util
from tasks.util import run


@task(aliases=['i'])
def install(c):
    """Install vscode with required extensions"""
    run(c,
        linux_in_docker_cmd=None,
        linux_cmd="sudo snap install --classic code",  # todo michel please test and remove comment if ok
        mac_os_cmd="brew install --cask visual-studio-code",
        windows_cmd="scoop install vscode")
    tasks.util.run("code --install-extension ms-vscode-remote.remote-containers --force")
    tasks.util.run("code --install-extension ms-azuretools.vscode-docker --force")
    tasks.util.run("code --install-extension mhutchie.git-graph --force")
    tasks.util.run("code --install-extension sourcegraph.sourcegraph --force")


DISROOP_EMBEDDED_HIPSTER_ROOT_PATH = pathlib.Path(__file__).parent.absolute()


@task(aliases=['o'])
def open(c):
    """Open DisroopEmbeddedHipster in vscode"""
    c.run(f"code {DISROOP_EMBEDDED_HIPSTER_ROOT_PATH}")


@task(aliases=['u'])
def update(c):
    """Update vscode to newest version"""
    run(c,
        linux_in_docker_cmd=None,
        linux_cmd="sudo snap refresh code",  # todo michel please test and remove comment if ok
        mac_os_cmd="brew upgrade vscode",
        windows_cmd="scoop update vscode")

@task
def uninstall(c):
    """Uninstall vscode"""
    run(c,
        linux_in_docker_cmd=None,
        linux_cmd="sudo snap remove code",  # todo michel please test and remove comment if ok
        mac_os_cmd="brew uninstall --cask visual-studio-code",
        windows_cmd="scoop uninstall vscode")
