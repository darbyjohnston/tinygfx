set(HEADERS
    IApp.h
    IWindow.h)
set(PRIVATE_HEADERS)

set(SOURCE)
if ("${TINYGFX_API}" STREQUAL "GL_4_1" OR
    "${TINYGFX_API}" STREQUAL "GL_4_1_Debug" OR
    "${TINYGFX_API}" STREQUAL "GLES_2")
    list(APPEND SOURCE
        IAppGL.cpp
        IWindowGL.cpp)
endif()

set(LIBRARIES)
if ("${TINYGFX_API}" STREQUAL "GL_4_1" OR
    "${TINYGFX_API}" STREQUAL "GL_4_1_Debug" OR
    "${TINYGFX_API}" STREQUAL "GLES_2")
    list(APPEND LIBRARIES tgGL)
endif()
list(APPEND LIBRARIES tgRender tgBaseApp)

add_library(tgUIApp ${HEADERS} ${PRIVATE_HEADERS} ${SOURCE})
target_link_libraries(tgUIApp ${LIBRARIES})
set_target_properties(tgUIApp PROPERTIES FOLDER lib)
set_target_properties(tgUIApp PROPERTIES PUBLIC_HEADER "${HEADERS}")

install(TARGETS tgUIApp
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include/tinygfx/tgUIApp)

