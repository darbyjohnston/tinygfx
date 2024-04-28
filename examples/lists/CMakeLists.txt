add_executable(lists lists.h lists.cpp)
target_link_libraries(lists tgUIApp)
set_target_properties(lists PROPERTIES FOLDER examples)

install(TARGETS lists
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)

add_test(NAME lists COMMAND lists -exit -log)
