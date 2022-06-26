set(HEADERS
	Assert.h
	Image.h
	Math.h
	MathInline.h
	Matrix.h
	MatrixInline.h
	Random.h
	Range.h
	RangeInline.h
	String.h
	StringFormat.h
	StringFormatInline.h
	Vector.h
	VectorInline.h)

set(SOURCE
	Assert.cpp
	Image.cpp
	Matrix.cpp
	Random.cpp
	Range.cpp
	String.cpp
	StringFormat.cpp
	Vector.cpp)

set(LIBRARIES)
set(LIBRARIES_PRIVATE Threads::Threads)

add_library(tgCore ${HEADERS} ${SOURCE})
target_link_libraries(tgCore PUBLIC ${LIBRARIES} PRIVATE ${LIBRARIES_PRIVATE})
set_target_properties(tgCore PROPERTIES FOLDER lib)
set_target_properties(tgCore PROPERTIES PUBLIC_HEADER "${HEADERS}")

install(TARGETS tgCore
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include/tinygfx/tgCore)
