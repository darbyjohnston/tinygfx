set(HEADERS
	Mesh.h
	OffscreenBuffer.h
	Shader.h
	Texture.h)

set(SOURCE
	Mesh.cpp
	OffscreenBuffer.cpp
	Shader.cpp
	Texture.cpp)

set(LIBRARIES tgCore tgGlad)
set(LIBRARIES_PRIVATE)

add_library(tgGL ${HEADERS} ${SOURCE})
target_link_libraries(tgGL PUBLIC ${LIBRARIES} PRIVATE ${LIBRARIES_PRIVATE})
set_target_properties(tgGL PROPERTIES FOLDER lib)
set_target_properties(tgGL PROPERTIES PUBLIC_HEADER "${HEADERS}")

install(TARGETS tgGL
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include/tinygfx/tgGL)
