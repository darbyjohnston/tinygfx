set(HEADERS
    lists.h)
set(PRIVATE_HEADERS)

set(SOURCE
    lists.cpp)

add_executable(lists ${HEADERS} ${PRIVATE_HEADERS} ${SOURCE})
target_link_libraries(lists tgUIApp)
set_target_properties(lists PROPERTIES FOLDER examples)

install(TARGETS lists
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)

