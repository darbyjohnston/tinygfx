set(HEADERS
    BoxPackTest.h
    BoxTest.h
    ColorTest.h
    ErrorTest.h
    FileIOTest.h
    FileTest.h
    FontSystemTest.h
    FormatTest.h
    ImageTest.h
    LRUCacheTest.h
    MathTest.h
    MatrixTest.h
    MemoryTest.h
    MeshTest.h
    OSTest.h
    ObservableTest.h
    RangeTest.h
    SizeTest.h
    StringTest.h
    SystemTest.h
    TimeTest.h
    TimerTest.h
    VectorTest.h)
set(PRIVATE_HEADERS)

set(SOURCE
    BoxPackTest.cpp
    BoxTest.cpp
    ColorTest.cpp
    ErrorTest.cpp
    FileIOTest.cpp
    FileTest.cpp
    FontSystemTest.cpp
    FormatTest.cpp
    ImageTest.cpp
    LRUCacheTest.cpp
    MathTest.cpp
    MatrixTest.cpp
    MemoryTest.cpp
    MeshTest.cpp
    OSTest.cpp
    ObservableTest.cpp
    RangeTest.cpp
    SizeTest.cpp
    StringTest.cpp
    SystemTest.cpp
    TimeTest.cpp
    TimerTest.cpp
    VectorTest.cpp)

add_library(tgCoreTest ${HEADERS} ${PRIVATE_HEADERS} ${SOURCE})
target_link_libraries(tgCoreTest tgTestLib)
set_target_properties(tgCoreTest PROPERTIES FOLDER tests)
set_target_properties(tgCoreTest PROPERTIES PUBLIC_HEADER "${HEADERS}")

