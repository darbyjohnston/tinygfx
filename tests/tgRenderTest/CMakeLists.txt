set(HEADERS
    ImageOptionsTest.h)
set(PRIVATE_HEADERS)

set(SOURCE
    ImageOptionsTest.cpp)

add_library(tgRenderTest ${HEADERS} ${PRIVATE_HEADERS} ${SOURCE})
target_link_libraries(tgRenderTest tgRender tgTestLib)
set_target_properties(tgRenderTest PROPERTIES FOLDER tests)
set_target_properties(tgRenderTest PROPERTIES PUBLIC_HEADER "${HEADERS}")

