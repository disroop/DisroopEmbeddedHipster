import os


def run(c, linux_in_docker_cmd=None, linux_cmd=None, mac_os_cmd=None, windows_cmd=None):
    from sys import platform
    if platform == "linux" or platform == "linux2" and in_disroop_docker_container() and linux_in_docker_cmd:
        c.run(linux_in_docker_cmd)
    elif platform == "linux" or platform == "linux2" and linux_cmd:
        c.run(linux_cmd)
    elif platform == "darwin" and mac_os_cmd:
        c.run(mac_os_cmd)
    elif platform == "win32" and windows_cmd:
        c.run(windows_cmd)


def in_disroop_docker_container() -> bool:
    return os.environ.get("AM_I_IN_A_DISROOP_DOCKER_CONTAINER", False)
