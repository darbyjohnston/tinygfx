set(HEADERS
    App.h
    TextWidget.h
    Window.h)

set(SOURCE
    App.cpp
    TextWidget.cpp
    Window.cpp
    main.cpp)

add_executable(textedit ${HEADERS} ${SOURCE})
target_link_libraries(textedit tgUIApp)
set_target_properties(textedit PROPERTIES FOLDER examples)

add_test(textedit ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/textedit${CMAKE_EXECUTABLE_SUFFIX} -exit)

install(TARGETS textedit
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)

