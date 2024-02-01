set(HEADERS
    filebrowser.h)
set(PRIVATE_HEADERS)

set(SOURCE
    filebrowser.cpp)

add_executable(filebrowser ${HEADERS} ${PRIVATE_HEADERS} ${SOURCE})
target_link_libraries(filebrowser tgUIApp)
set_target_properties(filebrowser PROPERTIES FOLDER examples)

install(TARGETS filebrowser
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)

