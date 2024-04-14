include(ExternalProject)

set(TINYGFX_ARGS
    ${TINYGFX_DEPS_ARGS}
    -DTINYGFX_API=${TINYGFX_API}
    -DTINYGFX_NFD=${TINYGFX_NFD}
    -DTINYGFX_PYTHON=${TINYGFX_PYTHON}
    -DTINYGFX_TESTS=${TINYGFX_TESTS}
    -DTINYGFX_GCOV=${TINYGFX_GCOV}
    -DTINYGFX_GPROF=${TINYGFX_GPROF})

ExternalProject_Add(
    tinygfx
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/tinygfx
    DEPENDS ${TINYGFX_DEPS}
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../..
    LIST_SEPARATOR |
    CMAKE_ARGS ${TINYGFX_ARGS})

