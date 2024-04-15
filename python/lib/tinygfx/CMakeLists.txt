pybind11_add_module(tinygfx Bindings.cpp)
target_link_libraries(tinygfx PRIVATE tgUIAppPy tgUIPy tgBaseAppPy tgCorePy)
set_target_properties(tinygfx PROPERTIES FOLDER python/lib)
set_target_properties(tinygfx PROPERTIES PUBLIC_HEADER "${HEADERS}")

install(TARGETS tinygfx
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)
