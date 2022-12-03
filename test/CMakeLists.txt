### Add GTest
add_subdirectory(googletest-release-1.12.1)
include_directories(googletest-release-1.12.1/googletest/include)
include(GoogleTest)
set(GTEST_LIB gtest gtest_main)

### parser_test
add_executable(parser_test parser_test.cpp)
target_link_libraries(parser_test
        parser
        ${GTEST_LIB})
### executor_test
add_executable(executor_test executor_test.cpp)
target_link_libraries(executor_test
        executor
        parser
        ${GTEST_LIB})

### storage_test
add_executable(storage_test storage_test.cpp)
target_link_libraries(storage_test
        storage
        parser
        executor
        ${GTEST_LIB})