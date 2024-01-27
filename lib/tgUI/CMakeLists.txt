set(HEADERS
    ButtonGroup.h
    CheckBox.h
    DrawUtil.h
    Event.h
    GridLayout.h
    GroupBox.h
    IButton.h
    IClipboard.h
    IPopup.h
    IWidget.h
    IWidgetInline.h
    IWindow.h
    Icon.h
    IconLibrary.h
    Init.h
    Label.h
    LayoutUtil.h
    ListButton.h
    PushButton.h
    RowLayout.h
    ScrollArea.h
    ScrollBar.h
    ScrollWidget.h
    Spacer.h
    StackLayout.h
    Style.h
    StyleInline.h
    ToolButton.h
    ToolTip.h
    WidgetOptions.h)
set(PRIVATE_HEADERS)

set(SOURCE
    ButtonGroup.cpp
    CheckBox.cpp
    DrawUtil.cpp
    Event.cpp
    GridLayout.cpp
    GroupBox.cpp
    IButton.cpp
    IClipboard.cpp
    IPopup.cpp
    IWidget.cpp
    IWindow.cpp
    Icon.cpp
    IconLibrary.cpp
    Init.cpp
    Label.cpp
    LayoutUtil.cpp
    ListButton.cpp
    PushButton.cpp
    RowLayout.cpp
    ScrollArea.cpp
    ScrollBar.cpp
    ScrollWidget.cpp
    Spacer.cpp
    StackLayout.cpp
    Style.cpp
    ToolButton.cpp
    ToolTip.cpp
    WidgetOptions.cpp)

add_library(tgUI ${HEADERS} ${PRIVATE_HEADERS} ${SOURCE})
target_link_libraries(tgUI tgIO tgRender)
set_target_properties(tgUI PROPERTIES FOLDER lib)
set_target_properties(tgUI PROPERTIES PUBLIC_HEADER "${HEADERS}")

install(TARGETS tgUI
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include/tinygfx/tgUI)

