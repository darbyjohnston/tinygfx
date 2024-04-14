set(HEADERS)
set(HEADERS_PRIVATE)
set(SOURCE
    IButton.cpp
    IWidget.cpp
    IWindow.cpp
    PushButton.cpp
    RowLayout.cpp
    Style.cpp
    WidgetOptions.cpp
    bindings.cpp)

pybind11_add_module(tgUIPy ${HEADERS} ${HEADERS_PRIVATE} ${SOURCE})
target_link_libraries(tgUIPy PRIVATE tgUI)
set_target_properties(tgUIPy PROPERTIES FOLDER python)
set_target_properties(tgUIPy PROPERTIES PUBLIC_HEADER "${HEADERS}")

install(TARGETS tgUIPy
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include/tinygfx/tgUIPy)
