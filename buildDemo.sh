#!/bin/bash
#!/bin/bash

rm -rf ./demo/build
conan install -if demo/build demo
conan build -bf demo/build demo

