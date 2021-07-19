#include <cstdlib>
#include <iostream>
#include <boost/program_options.hpp>

#include "parse.h"
#include "compiling.h"

using namespace std;
namespace po = boost::program_options;

int main(int argc, char *argv[])
{
    // cout << "argc == " << argc << '\n';
    parse();

    return EXIT_SUCCESS; 
}

