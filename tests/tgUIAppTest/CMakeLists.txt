set(HEADERS
    AppTest.h)
set(PRIVATE_HEADERS)

set(SOURCE
    AppTest.cpp)

add_library(tgUIAppTest ${HEADERS} ${PRIVATE_HEADERS} ${SOURCE})
target_link_libraries(tgUIAppTest tgUIApp tgTestLib)
set_target_properties(tgUIAppTest PROPERTIES FOLDER tests)
set_target_properties(tgUIAppTest PROPERTIES PUBLIC_HEADER "${HEADERS}")

