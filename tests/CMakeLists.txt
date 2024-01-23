add_subdirectory(tgBaseAppTest)
add_subdirectory(tgCoreTest)
add_subdirectory(tgTestLib)
add_subdirectory(tgtest)
if ("${TINYGFX_API}" STREQUAL "GL_4_1" OR
    "${TINYGFX_API}" STREQUAL "GL_4_1_Debug" OR
    "${TINYGFX_API}" STREQUAL "GLES_2")
    add_subdirectory(tgGLTest)
endif()

