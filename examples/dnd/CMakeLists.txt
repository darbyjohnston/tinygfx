add_executable(dnd dnd.h dnd.cpp)
target_link_libraries(dnd tgUIApp)
set_target_properties(dnd PROPERTIES FOLDER examples)

add_test(dnd ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/dnd${CMAKE_EXECUTABLE_SUFFIX} -exit)

install(TARGETS dnd
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)

