from invoke import task


@task(aliases=['g'])
def gen(c):
    """generate files used in the documentation"""
    # project cli commands
    c.run("inv -l --list-depth 1 > ./doc/project_commands.txt")
    c.run("inv -l > ./doc/all_commands.txt")
    c.run("inv -l code> ./doc/vscode_commands.txt")

    # conan graphs
    c.run("conan info ./blinky --graph doc/conan_graph_utest.dot")
    c.run("conan info ./blinky --graph doc/conan_graph_blinky_debug.dot -pr=.profiles/arm-m4-debug")
    # cmakegraphs
    # todo