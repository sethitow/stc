#include <algorithm>
#include <iostream>
#include <iterator>

#include <boost/program_options.hpp>

#include "compile.hpp"
#include "parse.hpp"

namespace po = boost::program_options;

int main(int argc, char *argv[])
{

    // Add options and their descriptions
    po::options_description desc("Options");
    desc.add_options()                           //
        ("help,h", "List of available commands") //
        ("version", "Current version")           //
        ("build", po::value<std::string>(), "Build and run the program");

    // Get the input from the command line and store it in a variable map
    po::variables_map vm;
    po::store(parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    // Output based on command
    if (vm.count("help"))
    {
        std::cout << desc << '\n';
    }
    else if (vm.count("version"))
    {
        std::cout << PROJECT_VERSION << '\n';
    }
    else if (vm.count("build"))
    {
        compile(vm["build"].as<std::string>());
    }

    return EXIT_SUCCESS;
};
