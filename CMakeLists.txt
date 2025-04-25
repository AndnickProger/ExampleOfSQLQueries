cmake_minimum_required(VERSION 3.10.0)
project(postgres VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDART 20)

include(CTest)
enable_testing()

set(PQXX /usr/local/include/pqxx)

find_library(PQXX_LIB pqxx)
find_library(PQ_LIB pq)

add_executable(postgres main.cpp)

target_link_libraries(postgres
                     ${PQXX_LIB}
                    ${PQ_LIB})

include(CPack)
