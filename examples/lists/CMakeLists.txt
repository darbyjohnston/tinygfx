add_executable(lists lists.h lists.cpp)
target_link_libraries(lists tgUIApp)
set_target_properties(lists PROPERTIES FOLDER examples)

add_test(lists ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/lists${CMAKE_EXECUTABLE_SUFFIX} -exit)

install(TARGETS lists
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)

