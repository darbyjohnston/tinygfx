set(HEADERS
    sol.h)
set(PRIVATE_HEADERS)

set(SOURCE
    sol.cpp)

add_executable(sol ${HEADERS} ${PRIVATE_HEADERS} ${SOURCE})
target_link_libraries(sol tgUIApp)
set_target_properties(sol PROPERTIES FOLDER examples)

install(TARGETS sol
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)

