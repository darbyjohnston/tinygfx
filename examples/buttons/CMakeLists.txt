add_executable(buttons buttons.h buttons.cpp)
target_link_libraries(buttons tgUIApp)
set_target_properties(buttons PROPERTIES FOLDER examples)

add_test(buttons ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/buttons${CMAKE_EXECUTABLE_SUFFIX} -exit)

install(TARGETS buttons
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)
