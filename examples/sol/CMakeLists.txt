set(HEADERS
	App.h
	ISol.h
	SolFactory.h
	Sol000.h
	Window.h)

set(SOURCE
	App.cpp
	ISol.cpp
	SolFactory.cpp
	Sol000.cpp
	Window.cpp
	main.cpp)

add_executable(sol ${HEADERS} ${SOURCE})
target_link_libraries(sol tgApp tgGL)
set_target_properties(sol PROPERTIES FOLDER examples)

install(
    TARGETS sol
    RUNTIME DESTINATION examples)
