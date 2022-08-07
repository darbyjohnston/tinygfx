set(HEADERS
	App.h
	Filter.h
	Window.h)

set(SOURCE
	App.cpp
	Filter.cpp
	Window.cpp
	main.cpp)

add_executable(filters ${HEADERS} ${SOURCE})
target_link_libraries(filters tgApp tgGL)
set_target_properties(filters PROPERTIES FOLDER examples)

install(
    TARGETS filters
    RUNTIME DESTINATION examples)
