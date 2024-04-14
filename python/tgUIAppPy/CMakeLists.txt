set(HEADERS)
set(HEADERS_PRIVATE)
set(SOURCE
    App.cpp
    Window.cpp
    bindings.cpp)

pybind11_add_module(tgUIAppPy ${HEADERS} ${HEADERS_PRIVATE} ${SOURCE})
target_link_libraries(tgUIAppPy PRIVATE tgUIApp)
set_target_properties(tgUIAppPy PROPERTIES FOLDER python)
set_target_properties(tgUIAppPy PROPERTIES PUBLIC_HEADER "${HEADERS}")

install(TARGETS tgUIAppPy
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include/tinygfx/tgUIAppPy)
