set(HEADERS tgtest.h)

set(SOURCE tgtest.cpp)

set(LIBRARIES
    tgBaseAppTest
    tgBaseApp
    tgCoreTest
    tgIOTest
    tgRenderTest)
if ("${TINYGFX_API}" STREQUAL "GL_4_1" OR
    "${TINYGFX_API}" STREQUAL "GL_4_1_Debug" OR
    "${TINYGFX_API}" STREQUAL "GLES_2")
    list(APPEND LIBRARIES tgGLTest)
endif()

add_executable(tgtest ${SOURCE} ${HEADERS})
target_link_libraries(tgtest ${LIBRARIES})
set_target_properties(tgtest PROPERTIES FOLDER tests)

add_test(tgtest ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/tgtest${CMAKE_EXECUTABLE_SUFFIX})
