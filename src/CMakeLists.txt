add_library(libstc parse.cpp
                   compile.cpp
                   lexer.cpp
                   token.cpp
                   token_stream.cpp
                   ast/expr_ast.cpp
                   ast/prototype_ast.cpp
                   ast/function_ast.cpp)

add_executable(stc main.cpp)
llvm_map_components_to_libnames(llvm_libs core)
target_link_libraries(stc libstc Boost::program_options ${llvm_libs})