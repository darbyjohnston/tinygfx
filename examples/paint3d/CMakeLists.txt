set(HEADERS
	App.h
	Mesh.h
	Obj.h
	Window.h)

set(SOURCE
	App.cpp
	Obj.cpp
	Mesh.cpp
	Window.cpp
	main.cpp)

add_executable(paint3d ${HEADERS} ${SOURCE})
target_link_libraries(paint3d tgApp tgGL)
set_target_properties(paint3d PROPERTIES FOLDER examples)

install(
    TARGETS paint3d
    RUNTIME DESTINATION examples)
