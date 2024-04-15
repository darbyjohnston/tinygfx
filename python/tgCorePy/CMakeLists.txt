set(HEADERS
    Bindings.h)
set(HEADERS_PRIVATE)
set(SOURCE
    Bindings.cpp
    Context.cpp
    OS.cpp
    Size.cpp)

add_library(tgCorePy ${HEADERS} ${HEADERS_PRIVATE} ${SOURCE})
target_link_libraries(tgCorePy tgCore Python3::Python)
set_target_properties(tgCorePy PROPERTIES FOLDER python)
set_target_properties(tgCorePy PROPERTIES PUBLIC_HEADER "${HEADERS}")
set_target_properties(tgCorePy PROPERTIES POSITION_INDEPENDENT_CODE ON)

install(TARGETS tgCorePy
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include/tinygfx/tgCorePy)
