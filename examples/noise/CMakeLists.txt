add_executable(noise noise.h noise.cpp)
target_link_libraries(noise dtk::dtkUIApp)
set_target_properties(noise PROPERTIES FOLDER examples)

add_test(NAME noise COMMAND noise -exit -log)
