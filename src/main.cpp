#include <cstdlib>
#include <iostream>
#include <boost/program_options.hpp>
#include <iterator>

#include "parse.h"
#include "compiling.h"

using namespace std;
namespace po = boost::program_options;



int main(int argc, char *argv[])
{
    // cout << "argc == " << argc << '\n';

    try {
        // Add options and their descriptions
        po::options_description desc("Options");
        desc.add_options()
            ("help,h", "List of available commands")
            ("version", "Current version")
            ("build", "Build and run the program");

        // Get the input from the command line and store it in a variable map
        po::variables_map vm;
        po::store(parse_command_line(argc, argv, desc), vm);
        po::notify(vm);

        // Output based on command
        if (vm.count("help"))
            std::cout << desc << '\n';
        else if (vm.count("version"))
            // std::cout << "Current version: " << vm["age"].as<float>() << '\n';
            std::cout << "Current version: 0.1" << '\n';
        else if (vm.count("build"))
            std::cout << "And this is where I would put my build functions..." << '\n';
    }

    catch(exception& e) {
        cerr << "error: " << e.what() << "\n";
        return 1;
    }
    catch(...) {
        cerr << "Exception of unknown type!\n";
    }

    return 0;
}