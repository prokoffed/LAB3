# Основная библиотека
add_library(lab3_lib STATIC tarithmeticexpression.cpp)
target_link_libraries(lab3_lib PUBLIC lab3_headers)
target_include_directories(lab3_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)