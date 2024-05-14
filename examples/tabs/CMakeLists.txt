add_executable(tabs tabs.cpp)
target_link_libraries(tabs tgUIApp)
set_target_properties(tabs PROPERTIES FOLDER examples)

install(TARGETS tabs
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)

add_test(NAME tabs COMMAND tabs -exit -log)
