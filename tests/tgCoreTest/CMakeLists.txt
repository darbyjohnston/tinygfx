set(HEADERS
    BoxPackTest.h
    BoxTest.h
    ColorTest.h
    CommandTest.h
    ErrorTest.h
    FileIOTest.h
    FileTest.h
    FontSystemTest.h
    FormatTest.h
    ImageIOTest.h
    ImageTest.h
    LRUCacheTest.h
    MathTest.h
    MatrixTest.h
    MemoryTest.h
    MeshTest.h
    NoiseTest.h
    OSTest.h
    ObservableTest.h
    PNGTest.h
    RandomTest.h
    RangeTest.h
    RenderOptionsTest.h
    RenderUtilTest.h
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
    CommandTest.cpp
    ErrorTest.cpp
    FileIOTest.cpp
    FileTest.cpp
    FontSystemTest.cpp
    FormatTest.cpp
    ImageIOTest.cpp
    ImageTest.cpp
    LRUCacheTest.cpp
    MathTest.cpp
    MatrixTest.cpp
    MemoryTest.cpp
    MeshTest.cpp
    NoiseTest.cpp
    OSTest.cpp
    ObservableTest.cpp
    PNGTest.cpp
    RandomTest.cpp
    RangeTest.cpp
    RenderOptionsTest.cpp
    RenderUtilTest.cpp
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

