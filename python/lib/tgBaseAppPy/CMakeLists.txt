set(HEADERS
    Bindings.h)
set(HEADERS_PRIVATE)
set(SOURCE
    Bindings.cpp
    CmdLine.cpp
    IApp.cpp)

add_library(tgBaseAppPy ${HEADERS} ${HEADERS_PRIVATE} ${SOURCE})
target_link_libraries(tgBaseAppPy tgBaseApp Python3::Python)
set_target_properties(tgBaseAppPy PROPERTIES FOLDER python/lib)
set_target_properties(tgBaseAppPy PROPERTIES PUBLIC_HEADER "${HEADERS}")

install(TARGETS tgBaseAppPy
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include/tinygfx/tgBaseAppPy)
