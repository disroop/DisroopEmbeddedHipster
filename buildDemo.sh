#!/bin/bash
mumoco --remotes 

cd demo || exit

conan create --build=missing -o demo:sonar_scanner=True .