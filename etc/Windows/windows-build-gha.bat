set BUILD_TYPE=%1

git clone https://github.com/darbyjohnston/dtk.git
cmake -S dtk\etc\SuperBuild ^
  -B dtk\build ^
  -DCMAKE_BUILD_TYPE=%BUILD_TYPE% ^
  -DCMAKE_INSTALL_PREFIX=%CD%\install ^
  -DCMAKE_PREFIX_PATH=%CD%\install
cmake --build dtk\build -j 4 --config %BUILD_TYPE%

cmake -S tinygfx ^
  -B tinygfx\build ^
  -DCMAKE_BUILD_TYPE=%BUILD_TYPE% ^
  -DCMAKE_PREFIX_PATH=%CD%\install
cmake --build tinygfx\build -j 4 --config %BUILD_TYPE%

