#!/bin/bash

set -x

BUILD_TYPE=$1

# Update packages
sudo apt-get update

# Install lcov
if [[ $TINYGFX_GCOV = "ON" ]]
then
    sudo apt-get install lcov
fi

# Install OpenGL support
sudo apt-get install xorg-dev libglu1-mesa-dev mesa-common-dev mesa-utils xvfb
xvfb-run glxinfo

# Build
mkdir build
cd build
cmake ../etc/SuperBuild \
    -DCMAKE_BUILD_TYPE=$BUILD_TYPE \
    -DCMAKE_INSTALL_PREFIX=$PWD/install \
    -DCMAKE_PREFIX_PATH=$PWD/install \
    -DTINYGFX_API=$TINYGFX_API \
    -DTINYGFX_PYTHON=$TINYGFX_PYTHON \
    -DTINYGFX_TESTS=$TINYGFX_TESTS \
    -DTINYGFX_GCOV=$TINYGFX_GCOV
cmake --build . -j 4 --config $BUILD_TYPE

