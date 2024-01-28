add_subdirectory(tgBaseApp)
add_subdirectory(tgCore)
add_subdirectory(tgRender)
add_subdirectory(tgResourceApp)
add_subdirectory(tgUI)
add_subdirectory(tgUIApp)
if ("${TINYGFX_API}" STREQUAL "GL_4_1" OR
    "${TINYGFX_API}" STREQUAL "GL_4_1_Debug" OR
    "${TINYGFX_API}" STREQUAL "GLES_2")
    add_subdirectory(tgGL)
endif()

