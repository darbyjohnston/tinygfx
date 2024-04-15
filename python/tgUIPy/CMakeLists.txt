set(HEADERS
    Bindings.h)
set(HEADERS_PRIVATE)
set(SOURCE
    Bindings.cpp
    IButton.cpp
    IWidget.cpp
    IWindow.cpp
    PushButton.cpp
    RowLayout.cpp
    Style.cpp
    WidgetOptions.cpp)

add_library(tgUIPy ${HEADERS} ${HEADERS_PRIVATE} ${SOURCE})
target_link_libraries(tgUIPy tgUI Python3::Python)
set_target_properties(tgUIPy PROPERTIES FOLDER python)
set_target_properties(tgUIPy PROPERTIES PUBLIC_HEADER "${HEADERS}")
set_target_properties(tgUIPy PROPERTIES POSITION_INDEPENDENT_CODE ON)

install(TARGETS tgUIPy
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include/tinygfx/tgUIPy)
