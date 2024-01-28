set(HEADERS
    sliders.h)
set(PRIVATE_HEADERS)

set(SOURCE
    sliders.cpp)

add_executable(sliders ${HEADERS} ${PRIVATE_HEADERS} ${SOURCE})
target_link_libraries(sliders tgUIApp)
set_target_properties(sliders PROPERTIES FOLDER examples)

install(TARGETS sliders
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)

