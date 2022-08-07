set(HEADERS
	App.h
	Render.h
	Window.h)

set(SOURCE
	App.cpp
	Render.cpp
	Window.cpp
	main.cpp)

add_executable(bezier ${HEADERS} ${SOURCE})
target_link_libraries(bezier tgApp tgGL)
set_target_properties(bezier PROPERTIES FOLDER examples)

install(
    TARGETS bezier
    RUNTIME DESTINATION examples)
