cmake_minimum_required(VERSION 3.10)

project(stc VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(Boost_USE_STATIC_LIBS ON)
find_package(Boost 1.70 REQUIRED COMPONENTS program_options)
add_executable(stc src/main.cpp src/parse.cpp src/compile.cpp)
target_link_libraries(stc Boost::program_options)

