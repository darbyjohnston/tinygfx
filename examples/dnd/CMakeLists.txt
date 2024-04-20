add_executable(dnd dnd.h dnd.cpp)
target_link_libraries(dnd tgUIApp)
set_target_properties(dnd PROPERTIES FOLDER examples)

install(TARGETS dnd
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)

