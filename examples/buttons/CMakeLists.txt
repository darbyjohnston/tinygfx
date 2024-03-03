add_executable(buttons buttons.h buttons.cpp)
target_link_libraries(buttons tgUIApp)
set_target_properties(buttons PROPERTIES FOLDER examples)

install(TARGETS buttons
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)

