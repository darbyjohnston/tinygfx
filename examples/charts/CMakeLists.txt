set(HEADERS
    charts.h)
set(PRIVATE_HEADERS)

set(SOURCE
    charts.cpp)

add_executable(charts ${HEADERS} ${PRIVATE_HEADERS} ${SOURCE})
target_link_libraries(charts tgUIApp)
set_target_properties(charts PROPERTIES FOLDER examples)

install(TARGETS charts
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)

