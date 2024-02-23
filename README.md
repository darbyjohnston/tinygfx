[![License](https://img.shields.io/badge/License-BSD%203--Clause-blue.svg)](https://opensource.org/licenses/BSD-3-Clause)
[![Build Status](https://github.com/darbyjohnston/tinygfx/actions/workflows/ci-workflow.yml/badge.svg)](https://github.com/darbyjohnston/tinygfx/actions/workflows/ci-workflow.yml)
[![codecov](https://codecov.io/gh/codecov/example-cpp11-cmake/branch/master/graph/badge.svg)](https://codecov.io/gh/darbyjohnston/tinygfx)

tinygfx
=======
Small experiments with graphics programming.


Building
========

Building on Linux
-----------------
Clone the repository:
```
git clone https://github.com/darbyjohnston/tinygfx.git
```
Create a build directory:
```
mkdir build && cd build
```
Run CMake:
```
cmake ../tinygfx/etc/SuperBuild -DCMAKE_INSTALL_PREFIX=$PWD/install -DCMAKE_PREFIX_PATH=$PWD/install -DCMAKE_BUILD_TYPE=Debug
```
Start the build:
```
cmake --build . -j 4 --config Debug
```
Try running the `simple` example:
```
./tinygfx/src/tinygfx-build/examples/render/simple/simple
```

Building on macOS
-----------------
Clone the repository:
```
git clone https://github.com/darbyjohnston/tinygfx.git
```
Create a build directory:
```
mkdir build && cd build
```
Run CMake:
```
cmake ../tinygfx/etc/SuperBuild -DCMAKE_INSTALL_PREFIX=$PWD/install -DCMAKE_PREFIX_PATH=$PWD/install -DCMAKE_BUILD_TYPE=Debug
```
Start the build:
```
cmake --build . -j 4 --config Debug
```
Try running the `simple` example:
```
./tinygfx/src/tinygfx-build/examples/render/simple/simple
```

Notes for building on macOS
---------------------------
The CMake variable "CMAKE_OSX_ARCHITECTURES" can be used to specify the build
architecture:
```
-DCMAKE_OSX_ARCHITECTURES=x86_64
```
```
-DCMAKE_OSX_ARCHITECTURES=arm64
```

Building on Windows
-------------------
Clone the repository:
```
git clone https://github.com/darbyjohnston/tinygfx.git
```
Create a build directory:
```
mkdir build && cd build
```
Run CMake:
```
cmake ..\tinygfx\etc\SuperBuild -DCMAKE_INSTALL_PREFIX=%CD%\install -DCMAKE_PREFIX_PATH=%CD%\install -DCMAKE_BUILD_TYPE=Debug

```
Start the build:
```
cmake --build . -j 4 --config Debug
```
Try running the `simple` example:
```
.\tinygfx\src\tinygfx-build\examples\render\simple\Debug\simple
```

