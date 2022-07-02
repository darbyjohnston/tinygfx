set(HEADERS
    ITest.h
    ITestInline.h)
set(SOURCE
    ITest.cpp)

add_library(tgTestLib ${SOURCE} ${HEADERS})
target_link_libraries(tgTestLib tgCore)
set_target_properties(tgTestLib PROPERTIES FOLDER tests)
