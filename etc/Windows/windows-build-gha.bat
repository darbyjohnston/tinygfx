set BUILD_TYPE=%1

cmake -S tinygfx\etc\SuperBuild ^
    -B %BUILD_TYPE% ^
    -DCMAKE_INSTALL_PREFIX=%CD%\%BUILD_TYPE%\install ^
    -DCMAKE_PREFIX_PATH=%CD%\%BUILD_TYPE%\install ^
    -DCMAKE_BUILD_TYPE=%BUILD_TYPE%

cmake --build %BUILD_TYPE% -j 4 --config %BUILD_TYPE%
