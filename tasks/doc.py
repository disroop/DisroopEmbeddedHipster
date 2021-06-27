from invoke import task


@task(aliases=['g'])
def gen(c):
    """generate files used in the documentation"""
    c.run("inv -l --list-depth 1 > ./doc/project_commands.txt")
    c.run("inv -l > ./doc/all_commands.txt")
    c.run("inv -l code> ./doc/vscode_commands.txt")
