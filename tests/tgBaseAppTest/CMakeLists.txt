set(HEADERS
    AppTest.h
    CmdLineTest.h)
set(PRIVATE_HEADERS)

set(SOURCE
    AppTest.cpp
    CmdLineTest.cpp)

add_library(tgBaseAppTest ${HEADERS} ${PRIVATE_HEADERS} ${SOURCE})
target_link_libraries(tgBaseAppTest tgBaseApp tgTestLib)
set_target_properties(tgBaseAppTest PROPERTIES FOLDER tests)
set_target_properties(tgBaseAppTest PROPERTIES PUBLIC_HEADER "${HEADERS}")

