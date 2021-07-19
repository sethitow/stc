#include <cstdlib>
#include <iostream>

#include <boost/program_options.hpp>

namespace po = boost::program_options;

const char *HELP_TEXT = "fatal: improper command line invocation";

int main(int argc, char *argv[])
{
    po::options_description global("Global options");
    global.add_options()                                            //
        ("version", "Print version")                                //
        ("command", po::value<std::string>(), "command to execute") //
        ("subargs", po::value<std::vector<std::string>>(),
         "Arguments for command");

    po::positional_options_description pos;
    pos.add("command", 1).add("subargs", -1);

    po::variables_map vm;

    po::parsed_options parsed = po::command_line_parser(argc, argv)
                                    .options(global)
                                    .positional(pos)
                                    .allow_unregistered()
                                    .run();

    po::store(parsed, vm);

    if (vm.count("version"))
    {
        const char *ver = PROJECT_VERSION;
        std::cout << ver << std::endl;
        return EXIT_SUCCESS;
    }

    if (!vm.count("command"))
    {
        std::cerr << HELP_TEXT << std::endl;
        return EXIT_FAILURE;
    }

    std::string cmd = vm["command"].as<std::string>();
    if (cmd == "build")
    {
        po::options_description build_desc("build options");
        build_desc.add_options() //
            ("output,o", po::value<std::string>(), "Write output to <file>");

        // Collect all the unrecognized options from the first pass. This will
        // include the (positional) command name, so we need to erase that.
        std::vector<std::string> opts =
            po::collect_unrecognized(parsed.options, po::include_positional);
        opts.erase(opts.begin());

        // Parse again...
        po::store(po::command_line_parser(opts).options(build_desc).run(), vm);
    }

    return EXIT_SUCCESS;
}