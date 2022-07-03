set(HEADERS
	App.h
	Window.h)

set(SOURCE
	App.cpp
	Window.cpp
	main.cpp)

add_executable(paint2d ${HEADERS} ${SOURCE})
target_link_libraries(paint2d tgApp tgGL)
set_target_properties(paint2d PROPERTIES FOLDER examples)

install(
    TARGETS paint2d
    RUNTIME DESTINATION examples)
