set(HEADERS
	App.h
	ISol.h
	Sol000.h
	Sol001.h
	Window.h)

set(SOURCE
	App.cpp
	ISol.cpp
	Sol000.cpp
	Sol001.cpp
	Window.cpp
	main.cpp)

add_executable(sol ${HEADERS} ${SOURCE})
target_link_libraries(sol tgApp tgGL)
set_target_properties(sol PROPERTIES FOLDER examples)

install(
    TARGETS sol
    RUNTIME DESTINATION examples)
