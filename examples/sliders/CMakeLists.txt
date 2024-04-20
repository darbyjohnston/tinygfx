add_executable(sliders sliders.h sliders.cpp)
target_link_libraries(sliders tgUIApp)
set_target_properties(sliders PROPERTIES FOLDER examples)

add_test(sliders ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/sliders${CMAKE_EXECUTABLE_SUFFIX} -exit)

install(TARGETS sliders
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)

