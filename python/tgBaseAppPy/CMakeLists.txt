set(HEADERS)
set(HEADERS_PRIVATE)
set(SOURCE
    Cmdline.cpp
    IApp.cpp
    bindings.cpp)

add_library(tgBaseAppPy SHARED ${HEADERS} ${HEADERS_PRIVATE} ${SOURCE})
target_link_libraries(tgBaseAppPy tgBaseApp Python3::Python)
set_target_properties(tgBaseAppPy PROPERTIES SUFFIX ".pyd")
set_target_properties(tgBaseAppPy PROPERTIES FOLDER python)
set_target_properties(tgBaseAppPy PROPERTIES PUBLIC_HEADER "${HEADERS}")

install(TARGETS tgBaseAppPy
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include/tinygfx/tgBaseAppPy)
