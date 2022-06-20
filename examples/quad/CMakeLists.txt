add_executable(quad main.cpp)
target_link_libraries(quad tgApp tgGL)
set_target_properties(quad PROPERTIES FOLDER examples)

install(
    TARGETS quad
    RUNTIME DESTINATION examples)
