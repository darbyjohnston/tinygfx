set(HEADERS
    Bindings.h
    ButtonGroup.h
    CheckBox.h
    ColorPopup.h
    ColorSwatch.h
    ColorWidget.h
    DoubleEdit.h
    DoubleEditSlider.h
    DoubleModel.h
    DoubleSlider.h
    Event.h
    FloatEdit.h
    FloatEditSlider.h
    FloatModel.h
    FloatSlider.h
    GroupBox.h
    IButton.h
    IPopup.h
    IWidget.h
    IWidgetPopup.h
    IWindow.h
    IntEdit.h
    IntEditSlider.h
    IntModel.h
    IntSlider.h
    MDICanvas.h
    MDIWidget.h
    PushButton.h
    RowLayout.h
    ScrollArea.h
    ScrollWidget.h
    Style.h
    ToolButton.h
    WidgetOptions.h)
set(HEADERS_PRIVATE)
set(SOURCE
    Bindings.cpp
    ButtonGroup.cpp
    CheckBox.cpp
    ColorPopup.cpp
    ColorSwatch.cpp
    ColorWidget.cpp
    DoubleEdit.cpp
    DoubleEditSlider.cpp
    DoubleModel.cpp
    DoubleSlider.cpp
    Event.cpp
    FloatEdit.cpp
    FloatEditSlider.cpp
    FloatModel.cpp
    FloatSlider.cpp
    GroupBox.cpp
    IButton.cpp
    IPopup.cpp
    IWidget.cpp
    IWidgetPopup.cpp
    IWindow.cpp
    IntEdit.cpp
    IntEditSlider.cpp
    IntModel.cpp
    IntSlider.cpp
    MDICanvas.cpp
    MDIWidget.cpp
    PushButton.cpp
    RowLayout.cpp
    ScrollArea.cpp
    ScrollWidget.cpp
    Style.cpp
    ToolButton.cpp
    WidgetOptions.cpp)

add_library(tgUIPy ${HEADERS} ${HEADERS_PRIVATE} ${SOURCE})
target_link_libraries(tgUIPy tgUI Python3::Python)
set_target_properties(tgUIPy PROPERTIES FOLDER python/lib)
set_target_properties(tgUIPy PROPERTIES PUBLIC_HEADER "${HEADERS}")

install(TARGETS tgUIPy
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include/tinygfx/tgUIPy)
