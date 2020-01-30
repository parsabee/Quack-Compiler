#include "all.hpp"
#include "driver.hpp"
#include <getopt.h>


void usage() {
    std::cerr << "usage: qkc [options] quack_file\n";
}

void version() {
    std::cerr << "quack version 1.0.0\n";
}

void help() {
    usage();
    std::cerr << "\n";
    std::cerr << "options:\n";
    std::cerr << "  -o, --output=< output_file >\n";
    std::cerr << "  -j, --json              produces a json representation of the syntax tree\n";
    std::cerr << "  -h, --help\n";
    std::cerr << "  -v, --version\n";
}

int main(int argc, char *argv[]) {

    static struct option longopts[] = {
            {"output",  required_argument, nullptr, 'o'},
            {"json",    no_argument,       nullptr, 'j'},
            {"help",    no_argument,       nullptr, 'h'},
            {"version", no_argument,       nullptr, 'v'},
            {nullptr,   0,                 nullptr, 0  }
    };

    int json = 0;
    char *output_file = nullptr;

    int ch;
    while ((ch = getopt_long(argc, argv, "jhvo:", longopts, nullptr)) != -1) {
        switch (ch) {
            case 'j':
                json = 1;
                break;
            case 'h':
                help();
                exit(0);
            case 'v':
                version();
                exit(0);
            case 'o':
                output_file = optarg;
                break;
            default:
                usage();
                exit(1);
        }
    }
    argc -= optind;
    argv += optind;

    if (argc != 1) {
        usage();
        exit(1);
    }

    try {
        ast::Driver drv(argv[0], output_file);
        if (json)
            drv.json();
        else
            drv.compile();
    } catch (const std::exception &ex) {
        std::cerr << ex.what() << '\n';
        exit(1);
    }
    exit(0);
}
