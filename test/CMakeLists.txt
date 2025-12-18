# Тесты 
add_executable(tests test_main.cpp)
target_link_libraries(tests lab3_lib)

# Или с Google Test (если установлен)
if(GTEST_FOUND)
    add_executable(tests_gtest test_tarithmeticexpression.cpp)
    target_link_libraries(tests_gtest lab3_lib gtest gtest_main)
endif()