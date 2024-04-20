add_executable(filebrowser filebrowser.h filebrowser.cpp)
target_link_libraries(filebrowser tgUIApp)
set_target_properties(filebrowser PROPERTIES FOLDER examples)

add_test(filebrowser ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/filebrowser${CMAKE_EXECUTABLE_SUFFIX} -exit)

install(TARGETS filebrowser
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)

