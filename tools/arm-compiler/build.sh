#!/bin/bash
conan install -if tmp/build -pr:b=clang-linux -pr:h=gcc-nrf52840 -s:b build_type=Release -s:h build_type=Debug .
conan source -if install -sf src .
conan create  -pr:b=clang-linux -pr:h=gcc-nrf52840 -s:b build_type=Release -s:h build_type=Debug .