add_executable(mdi mdi.cpp)
target_link_libraries(mdi tgUIApp)
set_target_properties(mdi PROPERTIES FOLDER examples)

install(TARGETS mdi
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)

add_test(NAME mdi COMMAND mdi -exit -log)