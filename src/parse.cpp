#include "parse.hpp"

#include <fstream>
#include <sstream>

#include "lexer.hpp"

int parse(std::string filename)
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

    return EXIT_SUCCESS;
}
