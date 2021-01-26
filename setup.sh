#!/bin/sh

# Install GTest
git clone https://github.com/google/googletest
cd googletest
mkdir build
cd build
cmake ..
make
make install
cd ../..
rm -rf googletest