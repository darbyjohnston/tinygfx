add_executable(filebrowser filebrowser.h filebrowser.cpp)
target_link_libraries(filebrowser tgUIApp)
set_target_properties(filebrowser PROPERTIES FOLDER examples)

install(TARGETS filebrowser
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)

