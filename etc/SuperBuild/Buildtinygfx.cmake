include(ExternalProject)

set(tinygfx_DEPS dtk)
set(tinygfx_ARGS ${tinygfx_DEPS_ARGS})

ExternalProject_Add(
    tinygfx
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/tinygfx
    DEPENDS ${tinygfx_DEPS}
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../..
    INSTALL_COMMAND ""
    LIST_SEPARATOR |
    CMAKE_ARGS ${tinygfx_ARGS})

