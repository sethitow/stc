#include "parse.hpp"

#include <fstream>
#include <sstream>

#include "lexer.h"

int parse(std::string filename)
{
    std::ifstream inFile(filename);
    std::stringstream strFile;
    strFile << inFile.rdbuf();

    tokenizerFunc(strFile.str());
    display();

    return EXIT_SUCCESS;
}
