set(HEADERS
    ImageIOTest.h
    PNGTest.h)
set(PRIVATE_HEADERS)

set(SOURCE
    ImageIOTest.cpp
    PNGTest.cpp)

add_library(tgIOTest ${HEADERS} ${PRIVATE_HEADERS} ${SOURCE})
target_link_libraries(tgIOTest tgIO tgTestLib)
set_target_properties(tgIOTest PROPERTIES FOLDER tests)
set_target_properties(tgIOTest PROPERTIES PUBLIC_HEADER "${HEADERS}")

