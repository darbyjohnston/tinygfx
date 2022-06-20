set(HEADERS
	gl.h
	khrplatform.h)

set(SOURCE
	gl.c)

add_library(tgGlad ${HEADERS} ${SOURCE})
target_link_libraries(tgGlad OpenGL::GL ${CMAKE_DL_LIBS})
set_target_properties(tgGlad PROPERTIES FOLDER deps)
set_target_properties(tgGlad PROPERTIES PUBLIC_HEADER "${HEADERS}")

install(
    TARGETS tgGlad
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include/tlRender/tgGlad)
