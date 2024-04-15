set(HEADERS
    Bindings.h)
set(HEADERS_PRIVATE)
set(SOURCE
    App.cpp
    Bindings.cpp
    Window.cpp)

add_library(tgUIAppPy ${HEADERS} ${HEADERS_PRIVATE} ${SOURCE})
target_link_libraries(tgUIAppPy tgUIApp Python3::Python)
set_target_properties(tgUIAppPy PROPERTIES FOLDER python/lib)
set_target_properties(tgUIAppPy PROPERTIES PUBLIC_HEADER "${HEADERS}")

install(TARGETS tgUIAppPy
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include/tinygfx/tgUIAppPy)
