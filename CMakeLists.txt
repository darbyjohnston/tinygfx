cmake_minimum_required(VERSION 3.22)
cmake_policy(SET CMP0091 NEW)
cmake_policy(SET CMP0114 NEW)
if(POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
endif()

project(
    tinygfx
    LANGUAGES CXX C)

#-------------------------------------------------------------------------------
# Options

set(TINYGFX_GPROF FALSE CACHE BOOL "Enable gprof code profiling")

#-------------------------------------------------------------------------------
# Configuration

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_FIND_FRAMEWORK LAST)

if(CMAKE_BUILD_TYPE MATCHES "^Debug$")
    add_definitions(-DDTK_ASSERT)
endif()

if(TINYGFX_GPROF)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pg")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pg")
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

#-------------------------------------------------------------------------------
# Dependencies

find_package(dtk REQUIRED)

#-------------------------------------------------------------------------------
# Subdirectories

add_subdirectory(examples)
