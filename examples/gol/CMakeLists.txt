add_executable(gol gol.h gol.cpp)
target_link_libraries(gol dtk::dtkUIApp)
set_target_properties(gol PROPERTIES FOLDER examples)

add_test(NAME gol COMMAND gol -exit -log)
