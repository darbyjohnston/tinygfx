set(HEADERS
    App.h
    IWindow.h)

set(SOURCE
	App.cpp
	IWindow.cpp)

set(LIBRARIES tgCore glfw)
set(LIBRARIES_PRIVATE)

add_library(tgApp ${HEADERS} ${SOURCE})
target_link_libraries(tgApp PUBLIC ${LIBRARIES} PRIVATE ${LIBRARIES_PRIVATE})
set_target_properties(tgApp PROPERTIES FOLDER lib)
set_target_properties(tgApp PROPERTIES PUBLIC_HEADER "${HEADERS}")

install(TARGETS tgApp
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include/tinygfx/tgApp)
