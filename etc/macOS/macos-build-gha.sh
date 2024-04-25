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
    -DTINYGFX_NFD=$TINYGFX_NFD \
    -DTINYGFX_PYTHON=$TINYGFX_PYTHON \
    -DTINYGFX_TESTS=$TINYGFX_TESTS \
    -DTINYGFX_EXAMPLES=$TINYGFX_EXAMPLES \
    -DTINYGFX_GCOV=$TINYGFX_GCOV \
    -DCMAKE_OSX_DEPLOYMENT_TARGET=${CMAKE_OSX_DEPLOYMENT_TARGET} \
    -DCMAKE_OSX_ARCHITECTURES=${CMAKE_OSX_ARCHITECTURES}
cmake --build . -j 4 --config $BUILD_TYPE

