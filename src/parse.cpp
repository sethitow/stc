#include "parse.hpp"

#include <fstream>
#include <sstream>

#include "lexer.hpp"

int parse(std::string filename)
{
    std::ifstream inFile(filename);
    std::stringstream strFile;
    strFile << inFile.rdbuf();

    auto tokens = tokenize(strFile.str());

    return EXIT_SUCCESS;
}
