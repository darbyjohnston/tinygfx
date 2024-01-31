set(HEADERS
    gol.h)
set(PRIVATE_HEADERS)

set(SOURCE
    gol.cpp)

add_executable(gol ${HEADERS} ${PRIVATE_HEADERS} ${SOURCE})
target_link_libraries(gol tgUIApp)
set_target_properties(gol PROPERTIES FOLDER examples)

install(TARGETS gol
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)

