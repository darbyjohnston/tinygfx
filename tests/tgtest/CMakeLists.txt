add_executable(tgtest main.cpp)
target_link_libraries(tgtest tgCoreTest)
set_target_properties(tgtest PROPERTIES FOLDER tests)

add_test(tgtest ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/tgtest${CMAKE_EXECUTABLE_SUFFIX})
