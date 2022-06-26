set(HEADERS
	App.h
	Sol.h
	Window.h)

set(SOURCE
	App.cpp
	Sol.cpp
	Window.cpp
	main.cpp)

add_executable(sol ${HEADERS} ${SOURCE})
target_link_libraries(sol tgApp tgGL)
set_target_properties(sol PROPERTIES FOLDER examples)

install(
    TARGETS sol
    RUNTIME DESTINATION examples)
