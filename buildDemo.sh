#!/bin/bash
mumoco --remotes 

cd demo || exit

conan create -o demo:sonar_scanner=True .