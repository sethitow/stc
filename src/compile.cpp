#include "compile.hpp"

#include <fstream>
#include <sstream>
#include <string>

#include "lexer.hpp"
#include "parse.hpp"

int compile(std::string filename)
{

    std::stringstream strFile;
    {
        std::ifstream inFile(filename);
        strFile << inFile.rdbuf();
    }

    auto tokens = tokenize(strFile.str());

    {
        std::ofstream outFile(filename + ".tok");
        for (const auto &tok : tokens.to_vec())
        {
            outFile << tok.to_string() << "\n";
        }
    }

    auto ast = parse(tokens);

    auto ctx = CodeGenContext(filename);
    ast->codegen(ctx);

    {
        std::error_code EC;
        llvm::raw_fd_ostream ll_dest(filename + ".ll", EC);
        if (EC)
        {
            llvm::errs() << "Could not open file: " << EC.message();
            return EXIT_FAILURE;
        }
        ctx.llvm_module->print(ll_dest, nullptr);
    }

    return EXIT_SUCCESS;
}
