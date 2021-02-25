#!/bin/bash
conan install -if tmp/build -pr:b=clang-linux -pr:h=gcc-nrf52840 -s:b build_type=Release -s:h build_type=Debug .
conan source -if tmp/build -sf  tmp/src .
conan build -if tmp/build -sf tmp/src -bf tmp/build .
conan package -bf tmp/build -if tmp/install -pf tmp/package -sf tmp/src .