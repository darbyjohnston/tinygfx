set(HEADERS ITest.h)
set(PRIVATE_HEADERS)

set(SOURCE ITest.cpp)

add_library(tgTestLib ${HEADERS} ${PRIVATE_HEADERS} ${SOURCE})
target_link_libraries(tgTestLib tgCore)
set_target_properties(tgTestLib PROPERTIES FOLDER lib)
set_target_properties(tgTestLib PROPERTIES PUBLIC_HEADER "${HEADERS}")

