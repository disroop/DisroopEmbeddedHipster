#!/bin/sh
BASEDIR=$(dirname "$0")
conan config install $BASEDIR/conan_config
NRF5CONANFILE=$BASEDIR/../nrf5sdk/conanfile.py
conan remove "*" -f
conan export "$NRF5CONANFILE" local-dev@disroop/development