set(HEADERS
	Assert.h
	BBox.h
	BBoxInline.h
	BBox2.h
	BBox2Inline.h
	BBox3.h
	BBox3Inline.h
	Error.h
    File.h
    FileIO.h
    FileInfo.h
    FileInfoInline.h
	Image.h
	ListObserver.h
	ListObserverInline.h
	MapObserver.h
	MapObserverInline.h
	Math.h
	MathInline.h
	Matrix.h
	MatrixInline.h
	Matrix3.h
	Matrix3Inline.h
	Matrix4.h
	Matrix4Inline.h
	Memory.h
	MemoryInline.h
	Mesh.h
	Observer.h
	Path.h
	PathInline.h
	Random.h
	Range.h
	RangeInline.h
	String.h
	StringFormat.h
	StringFormatInline.h
	Util.h
	ValueObserver.h
	ValueObserverInline.h
	Vector.h
	VectorInline.h
	Vector2.h
	Vector2Inline.h
	Vector3.h
	Vector3Inline.h
	Vector4.h
	Vector4Inline.h)

set(SOURCE
	Assert.cpp
	Error.cpp
    FileIO.cpp
    FileInfo.cpp
	Image.cpp
	Memory.cpp
	Mesh.cpp
	Path.cpp
	Random.cpp
	Range.cpp
	String.cpp
	StringFormat.cpp)

if (WIN32)
    set(SOURCE
        ${SOURCE}
		ErrorWin32.cpp
        FileIOWin32.cpp
        FileInfoWin32.cpp
        FileWin32.cpp)
else()
    set(SOURCE
        ${SOURCE}
        FileIOUnix.cpp
        FileInfoUnix.cpp
        FileUnix.cpp)
endif()

set(LIBRARIES)
set(LIBRARIES_PRIVATE fseq Threads::Threads)

add_library(tgCore ${HEADERS} ${SOURCE})
target_link_libraries(tgCore PUBLIC ${LIBRARIES} PRIVATE ${LIBRARIES_PRIVATE})
set_target_properties(tgCore PROPERTIES FOLDER lib)
set_target_properties(tgCore PROPERTIES PUBLIC_HEADER "${HEADERS}")

install(TARGETS tgCore
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include/tinygfx/tgCore)
