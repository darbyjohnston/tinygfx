add_subdirectory(tgBaseAppPy)
add_subdirectory(tgCorePy)
add_subdirectory(tgUIAppPy)
add_subdirectory(tgUIPy)

pybind11_add_module(tinygfx bindings.cpp)
target_link_libraries(tinygfx PRIVATE tgUIAppPy tgUIPy tgBaseAppPy tgCorePy)
set_target_properties(tinygfx PROPERTIES FOLDER python)
set_target_properties(tinygfx PROPERTIES PUBLIC_HEADER "${HEADERS}")

install(TARGETS tinygfx
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)
