set(HEADERS
    noise.h)
set(PRIVATE_HEADERS)

set(SOURCE
    noise.cpp)

add_executable(noise ${HEADERS} ${PRIVATE_HEADERS} ${SOURCE})
target_link_libraries(noise tgUIApp)
set_target_properties(noise PROPERTIES FOLDER examples)

install(TARGETS noise
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)

