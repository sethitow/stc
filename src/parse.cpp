#include <iostream>
#include <fstream>
#include "parse.hpp"

int parse(std::string filename) {
    std::cout << "Parsing " << filename << std::endl;

    std::string oneLine;
    std::ifstream inFile(filename);
    
    while (inFile) {
        getline(inFile, oneLine);
        std::cout << oneLine << std::endl;
    }
    inFile.close();
    
    return EXIT_SUCCESS;
}