set(HEADERS)
set(PRIVATE_HEADERS)

set(SOURCE
    main.cpp)

add_executable(tgresource ${HEADERS} ${PRIVATE_HEADERS} ${SOURCE})
target_link_libraries(tgresource tgResourceApp)
set_target_properties(tgresource PROPERTIES FOLDER bin)

install(TARGETS tgresource
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)

