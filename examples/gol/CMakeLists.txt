add_executable(gol gol.h gol.cpp)
target_link_libraries(gol dtk::dtkUI)
set_target_properties(gol PROPERTIES FOLDER examples)
