set(HEADERS)
set(HEADERS_PRIVATE)
set(SOURCE
    Cmdline.cpp
    IApp.cpp
    bindings.cpp)

pybind11_add_module(tgBaseAppPy ${HEADERS} ${HEADERS_PRIVATE} ${SOURCE})
target_link_libraries(tgBaseAppPy PRIVATE tgBaseApp)
set_target_properties(tgBaseAppPy PROPERTIES FOLDER python)
set_target_properties(tgBaseAppPy PROPERTIES PUBLIC_HEADER "${HEADERS}")

install(TARGETS tgBaseAppPy
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include/tinygfx/tgBaseAppPy)
