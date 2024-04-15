#!/bin/bash

set -x

BUILD_TYPE=$1

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

