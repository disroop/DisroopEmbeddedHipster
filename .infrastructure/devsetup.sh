#!/bin/sh
#echo "export CONAN_USER_HOME=/workspace" >> ~/.bashrc
#source ~/.bashrc
BASEDIR=$(dirname "$0")
NRF5BUILDDIR=$BASEDIR/../nrf5sdk/build
NRF5SOURCEDIR=$BASEDIR/../nrf5sdk/source
NRF5CONANFILE=$BASEDIR/../nrf5sdk/conanfile.py
#if [ ! -d "$NRF5SOURCEDIR" ]; then
#    rm -rf $NRF5BUILDDIR
#    rm -rf $NRF5SOURCEDIR
#    conan install -if "$NRF5BUILDDIR" "$NRF5CONANFILE"
#    conan source -sf "$NRF5SOURCEDIR" -if "$NRF5BUILDDIR" "$NRF5CONANFILE"
#fi
conan remove "*" -f
conan export "$NRF5CONANFILE" local-dev@disroop/development