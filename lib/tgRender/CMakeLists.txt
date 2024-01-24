set(HEADERS
    IRender.h
    ImageOptions.h
    ImageOptionsInline.h
    RenderOptions.h
    RenderOptionsInline.h)
set(PRIVATE_HEADERS)

set(SOURCE
    IRender.cpp
    ImageOptions.cpp)

add_library(tgRender ${HEADERS} ${PRIVATE_HEADERS} ${SOURCE})
target_link_libraries(tgRender tgCore)
set_target_properties(tgRender PROPERTIES FOLDER lib)
set_target_properties(tgRender PROPERTIES PUBLIC_HEADER "${HEADERS}")

install(TARGETS tgRender
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include/tinygfx/tgRender)

