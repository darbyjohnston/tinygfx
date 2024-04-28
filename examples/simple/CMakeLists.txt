add_executable(simple simple.h simple.cpp)
target_link_libraries(simple tgUIApp)
set_target_properties(simple PROPERTIES FOLDER examples)

install(TARGETS simple
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)

add_test(NAME simple COMMAND simple -exit -log)