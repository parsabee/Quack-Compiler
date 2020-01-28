#include "all.hpp"
#include "driver.hpp"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "invalid number of arguments\n";
        exit(1);
    }
    try {
        ast::Driver drv(std::cout, argv[1]);
        drv.compile();
    } catch (const std::exception &ex) {
        std::cerr << ex.what() << '\n';
        exit(1);
    }
    exit(0);
}
