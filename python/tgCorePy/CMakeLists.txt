set(HEADERS
    bindings.h)
set(HEADERS_PRIVATE)
set(SOURCE
    Context.cpp
    OS.cpp
    Size.cpp
    bindings.cpp)

add_library(tgCorePy ${HEADERS} ${HEADERS_PRIVATE} ${SOURCE})
target_link_libraries(tgCorePy tgCore Python3::Python)
set_target_properties(tgCorePy PROPERTIES FOLDER python)
set_target_properties(tgCorePy PROPERTIES PUBLIC_HEADER "${HEADERS}")

install(TARGETS tgCorePy
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include/tinygfx/tgCorePy)
