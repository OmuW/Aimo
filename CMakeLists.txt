cmake_minimum_required(VERSION 3.10)
project(aimo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES 
    src/fib.cpp
    src/Bitboard.cpp
)

set(HEADERS 
    include/fib.h
    include/Bitboard.h
)

add_library(aimo_lib ${SOURCES} ${HEADERS})
target_include_directories(aimo_lib PUBLIC ${CMAKE_SOURCE_DIR}/include PRIVATE ${CMAKE_SOURCE_DIR}/src)

add_executable(aimo src/main.cpp)
target_link_libraries(aimo PRIVATE aimo_lib)

enable_testing()
add_subdirectory(tests)
