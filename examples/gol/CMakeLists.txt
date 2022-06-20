set(HEADERS
	App.h
	GOL.h
	Buffer.h
	BufferInline.h
	Window.h)

set(SOURCE
	App.cpp
	GOL.cpp
	Window.cpp
	main.cpp)

add_executable(gol ${HEADERS} ${SOURCE})
target_link_libraries(gol tgApp tgGL)
set_target_properties(gol PROPERTIES FOLDER examples)

install(
    TARGETS gol
    RUNTIME DESTINATION examples)
