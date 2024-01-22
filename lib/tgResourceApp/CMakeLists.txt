set(HEADERS
    App.h)
set(PRIVATE_HEADERS)

set(SOURCE
    App.cpp)

add_library(tgResourceApp ${HEADERS} ${PRIVATE_HEADERS} ${SOURCE})
target_link_libraries(tgResourceApp tgBaseApp)
set_target_properties(tgResourceApp PROPERTIES FOLDER lib)
set_target_properties(tgResourceApp PROPERTIES PUBLIC_HEADER "${HEADERS}")

install(TARGETS tgResourceApp
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include/tinygfx/tgResourceApp)

