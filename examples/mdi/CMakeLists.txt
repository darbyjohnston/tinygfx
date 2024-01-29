set(HEADERS
    mdi.h)
set(PRIVATE_HEADERS)

set(SOURCE
    mdi.cpp)

add_executable(mdi ${HEADERS} ${PRIVATE_HEADERS} ${SOURCE})
target_link_libraries(mdi tgUIApp)
set_target_properties(mdi PROPERTIES FOLDER examples)

install(TARGETS mdi
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)

