[![License](https://img.shields.io/badge/License-BSD%203--Clause-blue.svg)](https://opensource.org/licenses/BSD-3-Clause)
[![Build Status](https://github.com/darbyjohnston/tinygfx/actions/workflows/ci-workflow.yml/badge.svg)](https://github.com/darbyjohnston/tinygfx/actions/workflows/ci-workflow.yml)

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
Run CMake:
```
cmake -S tinygfx/etc/SuperBuild -B Release -DCMAKE_INSTALL_PREFIX=$PWD/Release/install -DCMAKE_PREFIX_PATH=$PWD/Release/install -DCMAKE_BUILD_TYPE=Release
```
Start the build:
```
cmake --build Release -j 4 --config Release
```
Try running the `gol` example:
```
Release/tinygfx/src/tinygfx-build/examples/gol/gol
```

Building on macOS
-----------------
Clone the repository:
```
git clone https://github.com/darbyjohnston/tinygfx.git
```
Run CMake:
```
cmake -S tinygfx/etc/SuperBuild -B Release -DCMAKE_INSTALL_PREFIX=$PWD/Release/install -DCMAKE_PREFIX_PATH=$PWD/Release/install -DCMAKE_BUILD_TYPE=Release
```
Start the build:
```
cmake --build Release -j 4 --config Release
```
Try running the `gol` example:
```
Release/tinygfx/src/tinygfx-build/examples/gol/gol
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
Run CMake:
```
cmake -S tinygfx\etc\SuperBuild -B Release -DCMAKE_INSTALL_PREFIX=%CD%\Release\install -DCMAKE_PREFIX_PATH=%CD%\Release\install -DCMAKE_BUILD_TYPE=Release
```
Start the build:
```
cmake --build Release -j 4 --config Release
```
Try running the `gol` example:
```
Release\tinygfx\src\tinygfx-build\examples\gol\Release\gol
```

