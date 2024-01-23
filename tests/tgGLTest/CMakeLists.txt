set(HEADERS
    MeshTest.h
    OffscreenBufferTest.h
    RenderTest.h
    ShaderTest.h
    TextureAtlasTest.h
    TextureTest.h
    WindowTest.h)
set(PRIVATE_HEADERS)

set(SOURCE
    MeshTest.cpp
    OffscreenBufferTest.cpp
    RenderTest.cpp
    ShaderTest.cpp
    TextureAtlasTest.cpp
    TextureTest.cpp
    WindowTest.cpp)

add_library(tgGLTest ${HEADERS} ${PRIVATE_HEADERS} ${SOURCE})
target_link_libraries(tgGLTest tgGL tgTestLib)
set_target_properties(tgGLTest PROPERTIES FOLDER tests)
set_target_properties(tgGLTest PROPERTIES PUBLIC_HEADER "${HEADERS}")

