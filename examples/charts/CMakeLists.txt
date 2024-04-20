add_executable(charts charts.h charts.cpp)
target_link_libraries(charts tgUIApp)
set_target_properties(charts PROPERTIES FOLDER examples)

add_test(charts ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/charts${CMAKE_EXECUTABLE_SUFFIX} -exit)

install(TARGETS charts
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)

