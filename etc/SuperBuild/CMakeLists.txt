cmake_minimum_required(VERSION 3.22)
cmake_policy(SET CMP0091 NEW)
cmake_policy(SET CMP0114 NEW)
if(POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
endif()

project(tinygfx-SuperBuild)

#-------------------------------------------------------------------------------
# Options

if(APPLE)
    set(tinygfx_IGNORE_PREFIX_PATH_DEFAULT /opt/homebrew)
endif()
set(tinygfx_IGNORE_PREFIX_PATH ${tinygfx_IGNORE_PREFIX_PATH_DEFAULT} CACHE STRING "Ignore the given prefix path")

#-------------------------------------------------------------------------------
# Configuration

list(PREPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/Modules)

if(NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 17)
endif()
if(NOT BUILD_SHARED_LIBS)
    set(BUILD_SHARED_LIBS OFF)
endif()
if(NOT CMAKE_POSITION_INDEPENDENT_CODE)
    set(CMAKE_POSITION_INDEPENDENT_CODE ON)
endif()
if(tinygfx_IGNORE_PREFIX_PATH)
    set(CMAKE_IGNORE_PREFIX_PATH ${tinygfx_IGNORE_PREFIX_PATH})
endif()
if(WIN32)
    set(CMAKE_MSVC_RUNTIME_LIBRARY MultiThreaded$<$<CONFIG:Debug>:Debug>DLL)
endif()
if(APPLE)
    set(CMAKE_FIND_FRAMEWORK LAST)
endif()

# https://stackoverflow.com/questions/45414507/pass-a-list-of-prefix-paths-to-externalproject-add-in-cmake-args
string(REPLACE ";" "|" CMAKE_MODULE_PATH_TMP "${CMAKE_MODULE_PATH}")
string(REPLACE ";" "|" CMAKE_PREFIX_PATH_TMP "${CMAKE_PREFIX_PATH}")

set(tinygfx_DEPS_ARGS
    -DCMAKE_MODULE_PATH=${CMAKE_MODULE_PATH_TMP}
    -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}
    -DCMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH_TMP}
    -DCMAKE_POLICY_DEFAULT_CMP0091:STRING=NEW
    -DCMAKE_POLICY_DEFAULT_CMP0114:STRING=NEW
    -DCMAKE_FIND_FRAMEWORK=${CMAKE_FIND_FRAMEWORK}
    -DCMAKE_CXX_STANDARD=${CMAKE_CXX_STANDARD}
    -DCMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}
    -DCMAKE_C_FLAGS=${CMAKE_C_FLAGS}
    -DCMAKE_MSVC_RUNTIME_LIBRARY=${CMAKE_MSVC_RUNTIME_LIBRARY}
    -DCMAKE_VERBOSE_MAKEFILE=${CMAKE_VERBOSE_MAKEFILE}
    -DCMAKE_OSX_DEPLOYMENT_TARGET=${CMAKE_OSX_DEPLOYMENT_TARGET}
    -DCMAKE_OSX_ARCHITECTURES=${CMAKE_OSX_ARCHITECTURES}
    -DBUILD_SHARED_LIBS=${BUILD_SHARED_LIBS}
    -DCMAKE_POSITION_INDEPENDENT_CODE=${CMAKE_POSITION_INDEPENDENT_CODE})
string(REPLACE ";" " " tinygfx_DEPS_ARGS_TMP "${tinygfx_DEPS_ARGS}")
message("tinygfx_DEPS_ARGS: " ${tinygfx_DEPS_ARGS_TMP})

#-------------------------------------------------------------------------------
# Build

list(APPEND tinygfx_DEPS dtk-deps)
list(APPEND tinygfx_DEPS dtk)
foreach(DEP ${tinygfx_DEPS})
    include(Build${DEP})
endforeach()

include(Buildtinygfx)
