set(HEADERS
    ImageIO.h
    Init.h
    Options.h)
set(PRIVATE_HEADERS
    PNG.h)

set(SOURCE
    ImageIO.cpp
    Init.cpp
    Options.cpp
    PNG.cpp
    PNGRead.cpp
    PNGWrite.cpp)

add_library(tgIO ${HEADERS} ${PRIVATE_HEADERS} ${SOURCE})
target_link_libraries(tgIO tgCore PNG)
set_target_properties(tgIO PROPERTIES FOLDER lib)
set_target_properties(tgIO PROPERTIES PUBLIC_HEADER "${HEADERS}")

install(TARGETS tgIO
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include/tinygfx/tgIO)

