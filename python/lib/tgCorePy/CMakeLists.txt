set(HEADERS
    Bindings.h
    Box.h
    Bindings.h
    Color.h
    Context.h
    FontSystem.h
    IRender.h
    ISystem.h
    Image.h
    Memory.h
    OS.h
    Observable.h
    ObservableList.h
    ObservableListInline.h
    ObservableMap.h
    ObservableMapInline.h
    ObservableValue.h
    ObservableValueInline.h
    Random.h
    Range.h
    Size.h
    Vector.h)
set(HEADERS_PRIVATE)
set(SOURCE
    Box.cpp
    Bindings.cpp
    Color.cpp
    Context.cpp
    FontSystem.cpp
    IRender.cpp
    ISystem.cpp
    Image.cpp
    Memory.cpp
    OS.cpp
    Observable.cpp
    ObservableList.cpp
    ObservableMap.cpp
    ObservableValue.cpp
    Random.cpp
    Range.cpp
    Size.cpp
    Vector.cpp)

add_library(tgCorePy ${HEADERS} ${HEADERS_PRIVATE} ${SOURCE})
target_link_libraries(tgCorePy tgCore Python3::Python)
set_target_properties(tgCorePy PROPERTIES FOLDER python/lib)
set_target_properties(tgCorePy PROPERTIES PUBLIC_HEADER "${HEADERS}")

install(TARGETS tgCorePy
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include/tinygfx/tgCorePy)
