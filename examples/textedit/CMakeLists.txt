set(HEADERS
    textedit.h)
set(PRIVATE_HEADERS)

set(SOURCE
    textedit.cpp)

add_executable(textedit ${HEADERS} ${PRIVATE_HEADERS} ${SOURCE})
target_link_libraries(textedit tgUIApp)
set_target_properties(textedit PROPERTIES FOLDER examples)

install(TARGETS textedit
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)

