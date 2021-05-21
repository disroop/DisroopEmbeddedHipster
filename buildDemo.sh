#!/bin/bash

conan install -if demo/build demo
conan build -bf demo/build demo

