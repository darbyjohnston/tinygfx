add_executable(noise noise.h noise.cpp)
target_link_libraries(noise dtk::dtkUI)
set_target_properties(noise PROPERTIES FOLDER examples)
