#!/bin/bash
mumoco --remotes 

conan install -if demo/build demo
conan build -bf demo/build demo

