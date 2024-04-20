add_executable(noise noise.h noise.cpp)
target_link_libraries(noise tgUIApp)
set_target_properties(noise PROPERTIES FOLDER examples)

add_test(noise ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/noise${CMAKE_EXECUTABLE_SUFFIX} -exit)

install(TARGETS noise
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)

