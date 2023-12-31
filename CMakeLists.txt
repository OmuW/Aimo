cmake_minimum_required(VERSION 3.10)
project(aimo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES 
    src/Bitboard.cpp
    src/Board.cpp
    src/chess_utils.cpp
    src/Movegen.cpp
    src/Evaluation.cpp
)

set(HEADERS 
    include/Bitboard.h
    include/Board.h
    include/chess_utils.h
    include/Movegen.h
    include/Evaluation.h
)

add_library(aimo_lib ${SOURCES} ${HEADERS})
target_include_directories(aimo_lib PUBLIC ${CMAKE_SOURCE_DIR}/include PRIVATE ${CMAKE_SOURCE_DIR}/src)

add_executable(aimo src/main.cpp)
target_link_libraries(aimo PRIVATE aimo_lib)

enable_testing()
add_subdirectory(tests)
