set(HEADERS
	Assert.h
	BBox.h
	BBoxInline.h
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
	Memory.h
	MemoryInline.h
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
	VectorInline.h)

set(SOURCE
	Assert.cpp
	BBox.cpp
	Error.cpp
    FileIO.cpp
    FileInfo.cpp
	Image.cpp
	Matrix.cpp
	Memory.cpp
	Path.cpp
	Random.cpp
	Range.cpp
	String.cpp
	StringFormat.cpp
	Vector.cpp)

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
