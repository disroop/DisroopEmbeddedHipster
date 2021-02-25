#!/bin/sh
BASEDIR=$(dirname "$0")
conan config install $BASEDIR/conan_config
#NRF5CONANFILE=$BASEDIR/../nrf5sdk/conanfile.py
#conan remove "*" -f
#conan create "$NRF5CONANFILE" local-dev@disroop/development
#conan install -if .downloads nrf5sdk/local-dev@disroop/development