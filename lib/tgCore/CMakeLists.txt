set(HEADERS
    Assert.h
    Box.h
    BoxInline.h
    BoxPack.h
    Color.h
    ColorInline.h
    Context.h
    ContextInline.h
    Error.h
    FileIO.h
    FileIOInline.h
    File.h
    FontSystem.h
    FontSystemInline.h
    Format.h
    FormatInline.h
    ISystem.h
    ISystemInline.h
    Image.h
    ImageInline.h
    Init.h
    LogSystem.h
    LRUCache.h
    LRUCacheInline.h
    Math.h
    MathInline.h
    Matrix.h
    MatrixInline.h
    Memory.h
    MemoryInline.h
    Mesh.h
    MeshInline.h
    OS.h
    ObservableList.h
    ObservableListInline.h
    ObservableMap.h
    ObservableMapInline.h
    ObservableValue.h
    ObservableValueInline.h
    Range.h
    RangeInline.h
    Size.h
    SizeInline.h
    String.h
    Time.h
    Timer.h
    Vector.h
    VectorInline.h)
set(HEADERS_PRIVATE)
set(SOURCE
    Assert.cpp
    BoxPack.cpp
    Context.cpp
    Error.cpp
    FileIO.cpp
    FontSystem.cpp
    Format.cpp
    ISystem.cpp
    Image.cpp
    Init.cpp
    LogSystem.cpp
    Math.cpp
    Memory.cpp
    Mesh.cpp
    OS.cpp
    String.cpp
    Time.cpp
    Timer.cpp)
if(WIN32)
    list(APPEND SOURCE
        ErrorWin32.cpp
        FileIOWin32.cpp
        FileWin32.cpp
        OSWin32.cpp
        TimeWin32.cpp)
else()
    list(APPEND SOURCE
        FileIOUnix.cpp
        FileUnix.cpp
        OSUnix.cpp
        TimeUnix.cpp)
endif()

add_library(tgCore ${HEADERS} ${HEADERS_PRIVATE} ${SOURCE})
target_link_libraries(tgCore Freetype::Freetype ZLIB::ZLIB)
set_target_properties(tgCore PROPERTIES FOLDER lib)
set_target_properties(tgCore PROPERTIES PUBLIC_HEADER "${HEADERS}")

install(TARGETS tgCore
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include/tinygfx/tgCore)



