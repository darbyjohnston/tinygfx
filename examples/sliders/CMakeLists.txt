add_executable(sliders sliders.h sliders.cpp)
target_link_libraries(sliders tgUIApp)
set_target_properties(sliders PROPERTIES FOLDER examples)

install(TARGETS sliders
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)

