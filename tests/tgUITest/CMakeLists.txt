set(HEADERS
    App.h
    ButtonTest.h
    DoubleModelTest.h
    DragAndDropTest.h
    EventTest.h
    FileBrowserTest.h
    FloatModelTest.h
    GridLayoutTest.h
    IntModelTest.h
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
    DoubleModelTest.cpp
    DragAndDropTest.cpp
    EventTest.cpp
    FileBrowserTest.cpp
    FloatModelTest.cpp
    GridLayoutTest.cpp
    IntModelTest.cpp
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

