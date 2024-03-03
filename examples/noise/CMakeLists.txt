add_executable(noise noise.h noise.cpp)
target_link_libraries(noise tgUIApp)
set_target_properties(noise PROPERTIES FOLDER examples)

install(TARGETS noise
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)

