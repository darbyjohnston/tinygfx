set(HEADERS
    popups.h)
set(PRIVATE_HEADERS)

set(SOURCE
    popups.cpp)

add_executable(popups ${HEADERS} ${PRIVATE_HEADERS} ${SOURCE})
target_link_libraries(popups tgUIApp)
set_target_properties(popups PROPERTIES FOLDER examples)

install(TARGETS popups
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)

