cmake_minimum_required(VERSION 3.10)

project(stc VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(Boost_USE_STATIC_LIBS ON)
find_package(Boost 1.70 REQUIRED COMPONENTS program_options)

find_package(LLVM REQUIRED CONFIG)
include_directories(${LLVM_INCLUDE_DIRS})
separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS_LIST})

add_executable(stc src/main.cpp
                   src/parse.cpp
                   src/compile.cpp
                   src/lexer.cpp
                   src/token.cpp
                   src/token_stream.cpp
                   src/ast/expr_ast.cpp
                   src/ast/prototype_ast.cpp)

llvm_map_components_to_libnames(llvm_libs core)
target_link_libraries(stc Boost::program_options ${llvm_libs})

