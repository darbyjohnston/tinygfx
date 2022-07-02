set(HEADERS
    BBoxTest.h
    ErrorTest.h
    FileIOTest.h
    FileTest.h
	ListObserverTest.h
	MapObserverTest.h
    MathTest.h
	MatrixTest.h
    MemoryTest.h
    PathTest.h
    RangeTest.h
    StringTest.h
    StringFormatTest.h
	ValueObserverTest.h
	VectorTest.h)
set(SOURCE
    BBoxTest.cpp
    ErrorTest.cpp
    FileIOTest.cpp
    FileTest.cpp
	ListObserverTest.cpp
	MapObserverTest.cpp
    MathTest.cpp
	MatrixTest.cpp
    MemoryTest.cpp
    PathTest.cpp
    RangeTest.cpp
    StringTest.cpp
    StringFormatTest.cpp
	ValueObserverTest.cpp
	VectorTest.cpp)

add_library(tgCoreTest ${SOURCE} ${HEADERS})
target_link_libraries(tgCoreTest tgTestLib)
set_target_properties(tgCoreTest PROPERTIES FOLDER tests)
