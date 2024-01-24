set(HEADERS App.h)

set(SOURCE App.cpp main.cpp)

set(LIBRARIES
    tgCoreTest
    tgRenderTest
    tgBaseAppTest
    tgBaseApp)
if ("${TINYGFX_API}" STREQUAL "GL_4_1" OR
    "${TINYGFX_API}" STREQUAL "GL_4_1_Debug" OR
    "${TINYGFX_API}" STREQUAL "GLES_2")
    list(APPEND LIBRARIES tgGLTest)
endif()

add_executable(tgtest ${SOURCE} ${HEADERS})
target_link_libraries(tgtest ${LIBRARIES})
set_target_properties(tgtest PROPERTIES FOLDER tests)

add_test(tgtest ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/tgtest${CMAKE_EXECUTABLE_SUFFIX})
