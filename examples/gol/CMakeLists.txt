add_executable(gol gol.h gol.cpp)
target_link_libraries(gol tgUIApp)
set_target_properties(gol PROPERTIES FOLDER examples)

install(TARGETS gol
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)

add_test(NAME gol COMMAND gol -exit -log)
