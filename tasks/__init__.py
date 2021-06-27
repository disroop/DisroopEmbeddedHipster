import shutil

from invoke import Collection, task

from tasks import vscode, jlink, doc


@task(aliases=['c'])
def clean(c):
    """Cleans all created files"""
    folders = [".conan", "build", "cmake-build-debug"]
    for folder in folders:
        shutil.rmtree(folder, ignore_errors=True)


ns = Collection(clean)
ns.add_collection(Collection.from_module(vscode, name="code"))
ns.add_collection(Collection.from_module(jlink))
ns.add_collection(Collection.from_module(doc))
