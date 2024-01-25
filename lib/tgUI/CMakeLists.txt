set(HEADERS
    DrawUtil.h
    Event.h
    IClipboard.h
    Icon.h
    IconLibrary.h
    IPopup.h
    IWidget.h
    IWidgetInline.h
    IWindow.h
    Label.h
    LayoutUtil.h
    Style.h
    StyleInline.h
    ToolTip.h
    WidgetOptions.h)
set(PRIVATE_HEADERS)

set(SOURCE
    DrawUtil.cpp
    Event.cpp
    IClipboard.cpp
    Icon.cpp
    IconLibrary.cpp
    IPopup.cpp
    IWidget.cpp
    IWindow.cpp
    Label.cpp
    LayoutUtil.cpp
    Style.cpp
    ToolTip.cpp
    WidgetOptions.cpp)

add_library(tgUI ${HEADERS} ${PRIVATE_HEADERS} ${SOURCE})
target_link_libraries(tgUI tgRender)
set_target_properties(tgUI PROPERTIES FOLDER lib)
set_target_properties(tgUI PROPERTIES PUBLIC_HEADER "${HEADERS}")

install(TARGETS tgUI
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include/tinygfx/tgUI)

