add_executable(gol gol.h gol.cpp)
target_link_libraries(gol tgUIApp)
set_target_properties(gol PROPERTIES FOLDER examples)

add_test(gol ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/gol${CMAKE_EXECUTABLE_SUFFIX} -exit)

install(TARGETS gol
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)

