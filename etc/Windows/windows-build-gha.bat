set BUILD_TYPE=%1

mkdir build
cd build
cmake ..\etc\SuperBuild ^
  -DCMAKE_BUILD_TYPE=%BUILD_TYPE% ^
  -DCMAKE_INSTALL_PREFIX=install ^
  -DCMAKE_PREFIX_PATH=install ^
  -DTINYGFX_API=%TINYGFX_API% ^
  -DTINYGFX_TESTS=%TINYGFX_TESTS% ^
  -DTINYGFX_GCOV=%TINYGFX_GCOV%
cmake --build . -j 4 --config %BUILD_TYPE%

