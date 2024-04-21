set(HEADERS
    App.h
    EventTest.h
    FileBrowserTest.h
    MDIWidgetTest.h
    PushButtonTest.h
    StyleTest.h
    WidgetOptionsTest.h
    Window.h)
set(PRIVATE_HEADERS)

set(SOURCE
    App.cpp
    EventTest.cpp
    FileBrowserTest.cpp
    MDIWidgetTest.cpp
    PushButtonTest.cpp
    StyleTest.cpp
    WidgetOptionsTest.cpp
    Window.cpp)

add_library(tgUITest ${HEADERS} ${PRIVATE_HEADERS} ${SOURCE})
target_link_libraries(tgUITest tgUI tgTestLib)
set_target_properties(tgUITest PROPERTIES FOLDER tests)
set_target_properties(tgUITest PROPERTIES PUBLIC_HEADER "${HEADERS}")

