set(HEADERS
    EventTest.h
    FileBrowserTest.h
    MDIWidgetTest.h
    StyleTest.h
    WidgetOptionsTest.h)
set(PRIVATE_HEADERS)

set(SOURCE
    EventTest.cpp
    FileBrowserTest.cpp
    MDIWidgetTest.cpp
    StyleTest.cpp
    WidgetOptionsTest.cpp)

add_library(tgUITest ${HEADERS} ${PRIVATE_HEADERS} ${SOURCE})
target_link_libraries(tgUITest tgUI tgTestLib)
set_target_properties(tgUITest PROPERTIES FOLDER tests)
set_target_properties(tgUITest PROPERTIES PUBLIC_HEADER "${HEADERS}")

