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

    auto ast = parse(tokens.to_vec());

    return EXIT_SUCCESS;
}
