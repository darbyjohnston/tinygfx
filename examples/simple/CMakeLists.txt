add_executable(simple simple.h simple.cpp)
target_link_libraries(simple tgUIApp)
set_target_properties(simple PROPERTIES FOLDER examples)

add_test(simple ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/simple${CMAKE_EXECUTABLE_SUFFIX} -exit)

install(TARGETS simple
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)

