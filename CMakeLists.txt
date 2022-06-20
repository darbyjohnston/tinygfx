cmake_minimum_required(VERSION 3.18)
cmake_policy(SET CMP0091 NEW)

project(
    tinygfx
    VERSION 0.1
    DESCRIPTION "Tiny graphics library"
    LANGUAGES CXX)

#-------------------------------------------------------------------------------
# Build options

set(TINYGFX_ENABLE_COVERAGE FALSE CACHE BOOL "Enable code coverage")
set(TINYGFX_BUILD_EXAMPLES TRUE CACHE BOOL "Build examples")
set(TINYGFX_BUILD_TESTS TRUE CACHE BOOL "Build tests")

#-------------------------------------------------------------------------------
# Internal configuration

set(CMAKE_CXX_STANDARD 17)

if (TINYGFX_BUILD_TESTS)
    set(CTEST_OUTPUT_ON_FAILURE ON)
    enable_testing()
endif()

include_directories(
	${PROJECT_SOURCE_DIR}/deps
	${PROJECT_SOURCE_DIR}/lib)

if(TINYGFX_ENABLE_COVERAGE)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")# -fkeep-inline-functions")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage")# -fkeep-inline-functions")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
endif()

set(CMAKE_FIND_FRAMEWORK LAST)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

#-------------------------------------------------------------------------------
# Dependencies

find_package(Threads REQUIRED)
find_package(OpenGL REQUIRED)

include(FetchContent)
FetchContent_Declare(
  GLFW
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG        3.3.7)
FetchContent_MakeAvailable(GLFW)

#-------------------------------------------------------------------------------
# Sub-directories

add_subdirectory(deps/tgGlad)
add_subdirectory(lib)
if(TINYGFX_BUILD_EXAMPLES)
	add_subdirectory(examples)
endif()
if(TINYGFX_BUILD_TESTS)
	add_subdirectory(tests)
endif()
