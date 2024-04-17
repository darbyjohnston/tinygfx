set(HEADERS
    Bindings.h)
set(HEADERS_PRIVATE)
set(SOURCE
    Box.cpp
    Bindings.cpp
    Context.cpp
    OS.cpp
    Range.cpp
    Size.cpp
    Vector.cpp)

add_library(tgCorePy ${HEADERS} ${HEADERS_PRIVATE} ${SOURCE})
target_link_libraries(tgCorePy tgCore Python3::Python)
set_target_properties(tgCorePy PROPERTIES FOLDER python/lib)
set_target_properties(tgCorePy PROPERTIES PUBLIC_HEADER "${HEADERS}")

install(TARGETS tgCorePy
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include/tinygfx/tgCorePy)
