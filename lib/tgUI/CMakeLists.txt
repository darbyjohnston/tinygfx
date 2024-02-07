set(HEADERS
    Action.h
    Bellows.h
    ButtonGroup.h
    CheckBox.h
    ColorPopup.h
    ColorSwatch.h
    ColorWidget.h
    ComboBox.h
    Divider.h
    DoubleEdit.h
    DoubleEditSlider.h
    DoubleModel.h
    DoubleSlider.h
    DrawUtil.h
    DrivesModel.h
    Event.h
    GridLayout.h
    GroupBox.h
    FileBrowser.h
    FileBrowserPrivate.h
    FileEdit.h
    FloatEdit.h
    FloatEditSlider.h
    FloatModel.h
    FloatSlider.h
    IButton.h
    IClipboard.h
    IDialog.h
    IMenuPopup.h
    IPopup.h
    IWidget.h
    IWidgetInline.h
    IWidgetPopup.h
    IWindow.h
    IncButtons.h
    IntEdit.h
    IntEditSlider.h
    IntModel.h
    IntSlider.h
    Icon.h
    IconLibrary.h
    Init.h
    Label.h
    LayoutUtil.h
    LineEdit.h
    ListButton.h
    MDICanvas.h
    MDIWidget.h
    Menu.h
    MenuBar.h
    PushButton.h
    RecentFilesModel.h
    RowLayout.h
    ScrollArea.h
    ScrollBar.h
    ScrollWidget.h
    SearchBox.h
    Spacer.h
    Splitter.h
    StackLayout.h
    Style.h
    StyleInline.h
    ToolButton.h
    ToolTip.h
    WidgetOptions.h)
set(PRIVATE_HEADERS)

set(SOURCE
    Action.cpp
    Bellows.cpp
    ButtonGroup.cpp
    CheckBox.cpp
    ColorPopup.cpp
    ColorSwatch.cpp
    ColorWidget.cpp
    ComboBox.cpp
    Divider.cpp
    DoubleEdit.cpp
    DoubleEditSlider.cpp
    DoubleModel.cpp
    DoubleSlider.cpp
    DrawUtil.cpp
    DrivesModel.cpp
    Event.cpp
    FileBrowser.cpp
    FileBrowserButton.cpp
    FileBrowserDirectoryWidget.cpp
    FileBrowserPathsWidget.cpp
    FileBrowserSystem.cpp
    FileBrowserWidget.cpp
    FileEdit.cpp
    FloatEdit.cpp
    FloatEditSlider.cpp
    FloatModel.cpp
    FloatSlider.cpp
    GridLayout.cpp
    GroupBox.cpp
    IButton.cpp
    IClipboard.cpp
    IDialog.cpp
    IMenuPopup.cpp
    IPopup.cpp
    IWidget.cpp
    IWidgetPopup.cpp
    IWindow.cpp
    IncButtons.cpp
    IntEdit.cpp
    IntEditSlider.cpp
    IntModel.cpp
    IntSlider.cpp
    Icon.cpp
    IconLibrary.cpp
    Init.cpp
    Label.cpp
    LayoutUtil.cpp
    LineEdit.cpp
    ListButton.cpp
    MDICanvas.cpp
    MDIWidget.cpp
    Menu.cpp
    MenuBar.cpp
    PushButton.cpp
    RecentFilesModel.cpp
    RowLayout.cpp
    ScrollArea.cpp
    ScrollBar.cpp
    ScrollWidget.cpp
    SearchBox.cpp
    Spacer.cpp
    Splitter.cpp
    StackLayout.cpp
    Style.cpp
    ToolButton.cpp
    ToolTip.cpp
    WidgetOptions.cpp)

set(LIBRARIES_PRIVATE)
if(TINYGFX_NFD)
    list(APPEND LIBRARIES_PRIVATE NFD)
endif()

add_library(tgUI ${HEADERS} ${PRIVATE_HEADERS} ${SOURCE})
target_link_libraries(tgUI PUBLIC tgCore PRIVATE ${LIBRARIES_PRIVATE})
set_target_properties(tgUI PROPERTIES FOLDER lib)
set_target_properties(tgUI PROPERTIES PUBLIC_HEADER "${HEADERS}")

install(TARGETS tgUI
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include/tinygfx/tgUI)

