set(HEADERS
    Bindings.h)
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