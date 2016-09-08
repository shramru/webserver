#include <iostream>
#include "server.hpp"

int main(int argc, char* argv[]) {
    int c;
    std::string root_dir, port;
    size_t workers = 8;
    if (argc < 3)
        throw std::runtime_error("Enter port, root_dir and workers count via command arguments");

    while((c = getopt(argc, argv, "r:c:p:")) != -1) {
        switch (c) {
            case 'r':
                root_dir = optarg;
                break;
            case 'p':
                port = optarg;
                break;
            case 'c':
                workers = (size_t)strtol(optarg, NULL, 10);
                break;
            default:
                break;
        }
    }

    try {
        Server server("0.0.0.0", port, root_dir, workers);
        server.listen();
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}