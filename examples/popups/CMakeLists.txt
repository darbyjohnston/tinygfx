add_executable(popups popups.h popups.cpp)
target_link_libraries(popups tgUIApp)
set_target_properties(popups PROPERTIES FOLDER examples)

install(TARGETS popups
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)

