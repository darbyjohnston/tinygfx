set(HEADERS
    IApp.h
    CmdLineInline.h
    CmdLine.h)
set(PRIVATE_HEADERS)

set(SOURCE
    IApp.cpp
    CmdLine.cpp)

add_library(tgBaseApp ${HEADERS} ${PRIVATE_HEADERS} ${SOURCE})
target_link_libraries(tgBaseApp tgCore)
set_target_properties(tgBaseApp PROPERTIES FOLDER lib)
set_target_properties(tgBaseApp PROPERTIES PUBLIC_HEADER "${HEADERS}")

install(TARGETS tgBaseApp
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include/tinygfx/tgBaseApp)

