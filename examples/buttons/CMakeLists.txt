set(HEADERS
    buttons.h)
set(PRIVATE_HEADERS)

set(SOURCE
    buttons.cpp)

add_executable(buttons ${HEADERS} ${PRIVATE_HEADERS} ${SOURCE})
target_link_libraries(buttons tgUIApp)
set_target_properties(buttons PROPERTIES FOLDER examples)

install(TARGETS buttons
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)

