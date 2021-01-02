#!/bin/bash

conan install -pr gcc-nrf52840-debug -if build .
conan source -if build -sf source .
conan build -sf source -bf build .
conan package -bf build -if build -sf source -pf package .

conan create -pr gcc-nrf52840-debug .

conan test -pr gcc-nrf52840-debug -tbf test_package/build-simple test_package/conanfile.py nrf5sdk/local-dev