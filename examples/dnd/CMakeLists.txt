set(HEADERS
    dnd.h)
set(PRIVATE_HEADERS)

set(SOURCE
    dnd.cpp)

add_executable(dnd ${HEADERS} ${PRIVATE_HEADERS} ${SOURCE})
target_link_libraries(dnd tgUIApp)
set_target_properties(dnd PROPERTIES FOLDER examples)

install(TARGETS dnd
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)

