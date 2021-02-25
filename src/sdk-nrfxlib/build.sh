#!/bin/bash
conan install -if install .
conan source -if install -sf src .
conan build -if install -sf src -bf build .
conan package -bf build -if install -pf package -sf src .