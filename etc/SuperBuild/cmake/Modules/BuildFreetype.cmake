include(ExternalProject)

set(Freetype_GIT_REPOSITORY "https://github.com/freetype/freetype.git")
set(Freetype_GIT_TAG "VER-2-13-0")

set(Freetype_ARGS
    ${TINYGFX_DEPS_ARGS}
    -DCMAKE_INSTALL_LIBDIR=lib
    -DFT_WITH_ZLIB=ON
    -DCMAKE_DISABLE_FIND_PACKAGE_BZip2=TRUE
    -DCMAKE_DISABLE_FIND_PACKAGE_PNG=TRUE
    -DCMAKE_DISABLE_FIND_PACKAGE_HarfBuzz=TRUE
    -DCMAKE_DISABLE_FIND_PACKAGE_BrotliDec=TRUE)

ExternalProject_Add(
    Freetype
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/Freetype
    DEPENDS ZLIB
    GIT_REPOSITORY ${Freetype_GIT_REPOSITORY}
    GIT_TAG ${Freetype_GIT_TAG}
    LIST_SEPARATOR |
    CMAKE_ARGS ${Freetype_ARGS})
