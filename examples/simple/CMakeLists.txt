set(HEADERS
    simple.h)
set(PRIVATE_HEADERS)

set(SOURCE
    simple.cpp)

add_executable(simple ${HEADERS} ${PRIVATE_HEADERS} ${SOURCE})
target_link_libraries(simple tgUIApp)
set_target_properties(simple PROPERTIES FOLDER examples)

install(TARGETS simple
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)

