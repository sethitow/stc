add_definitions( -DPROJECT_VERSION="${CMAKE_PROJECT_VERSION}" )

add_library(libstc parse.cpp
                   compile.cpp
                   lexer.cpp
                   token.cpp
                   token_stream.cpp
                   ast/binary_expr_ast.cpp
                   ast/call_expr_ast.cpp
                   ast/function_ast.cpp
                   ast/number_expr_ast.cpp
                   ast/prototype_ast.cpp
                   ast/variable_expr_ast.cpp)

set_target_properties(libstc PROPERTIES PREFIX "")
add_executable(stc main.cpp)
target_link_libraries(stc libstc Boost::program_options ${llvm_libs})