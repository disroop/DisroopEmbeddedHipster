from invoke import task
import shutil
import os


def _generate_blinky_conan_graph(context, output_folder: str, file_name: str, build_arg: str = ""):
    context.run(f"conan info ./blinky --graph {output_folder}/{file_name}.dot {build_arg}")
    context.run(f"dot -Tpng {output_folder}/{file_name}.dot > {output_folder}/{file_name}.png")
    os.remove(f"{output_folder}/{file_name}.dot")


def _generate_blinky_cmake_graph(context, output_folder: str, file_name: str, build_folder: str,  build_arg: str):
    context.run(f"conan install  ./blinky  --install-folder={build_folder} {build_arg}")
    os.mkdir(f"{output_folder}/tmp")
    context.run(f'bash -c "source {build_folder}/activate.sh && cmake -S ./blinky -B {build_folder} --graphviz={output_folder}/tmp/cmake-target-graph.dot"')
    context.run(f"dot -Tpng {output_folder}/tmp/cmake-target-graph.dot > {output_folder}/{file_name}.png")
    shutil.rmtree(f"{output_folder}/tmp")


@task(aliases=['g'])
def gen(c):
    """generate files used in the documentation"""
    # project cli commands
    c.run("inv -l > ./doc/project_commands.txt")
    c.run("inv -l > ./doc/all_commands.txt")
    c.run("inv -l code> ./doc/vscode_commands.txt")

    # conan graphs
    _generate_blinky_conan_graph(c, "blinky/assets/doc-images", "conan_graph_utest")
    _generate_blinky_conan_graph(c, "blinky/assets/doc-images", "conan_graph_blinky", "-pr:h=.profiles/arm-m4-release -pr:b=default")

    # cmakegraphs
    # todo
    _generate_blinky_cmake_graph(c, output_folder="blinky/assets/doc-images", file_name="cmake_blinky_utest", build_folder="build/utest",  build_arg="--profile:build=default --profile:host=default --build missing -s:h build_type=Debug")
    _generate_blinky_cmake_graph(c, output_folder="blinky/assets/doc-images", file_name="cmake_blinky", build_folder="build/blinky-release",  build_arg="--profile:build=default --profile:host=/workspace/.profiles/arm-m4-release --build missing")
    
    
