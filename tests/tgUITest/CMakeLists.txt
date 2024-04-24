set(HEADERS
    App.h
    ButtonTest.h
    DoubleEditSliderTest.h
    DoubleEditTest.h
    DoubleModelTest.h
    DoubleSliderTest.h
    DragAndDropTest.h
    EventTest.h
    FileBrowserTest.h
    FloatEditSliderTest.h
    FloatEditTest.h
    FloatModelTest.h
    FloatSliderTest.h
    GridLayoutTest.h
    IntEditSliderTest.h
    IntEditTest.h
    IntModelTest.h
    IntSliderTest.h
    LineEditTest.h
    MDIWidgetTest.h
    RowLayoutTest.h
    StackLayoutTest.h
    StyleTest.h
    WidgetOptionsTest.h
    Window.h)
set(PRIVATE_HEADERS)

set(SOURCE
    App.cpp
    ButtonTest.cpp
    DoubleEditSliderTest.cpp
    DoubleEditTest.cpp
    DoubleModelTest.cpp
    DoubleSliderTest.cpp
    DragAndDropTest.cpp
    EventTest.cpp
    FileBrowserTest.cpp
    FloatEditSliderTest.cpp
    FloatEditTest.cpp
    FloatModelTest.cpp
    FloatSliderTest.cpp
    GridLayoutTest.cpp
    IntEditSliderTest.cpp
    IntEditTest.cpp
    IntModelTest.cpp
    IntSliderTest.cpp
    LineEditTest.cpp
    MDIWidgetTest.cpp
    RowLayoutTest.cpp
    StackLayoutTest.cpp
    StyleTest.cpp
    WidgetOptionsTest.cpp
    Window.cpp)

add_library(tgUITest ${HEADERS} ${PRIVATE_HEADERS} ${SOURCE})
target_link_libraries(tgUITest tgUI tgTestLib)
set_target_properties(tgUITest PROPERTIES FOLDER tests)
set_target_properties(tgUITest PROPERTIES PUBLIC_HEADER "${HEADERS}")
