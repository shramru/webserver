#include "server.hpp"

int main(int argc, char* argv[]) {
    int c;
    std::string root_dir, port;
    size_t workers = 8;

    try {
        if (argc < 3)
            throw std::invalid_argument("Enter port, root_dir and workers count via command arguments");

        while((c = getopt(argc, argv, "r:c:p:")) != -1) {
            switch (c) {
                case 'r':
                    root_dir = optarg;
                    break;
                case 'p':
                    port = optarg;
                    break;
                case 'c':
                    workers = (size_t)std::stoi(optarg);
                    break;
                default:
                    throw std::invalid_argument("Unsupported flag");
            }
        }

        Server server("0.0.0.0", port, root_dir, workers);
        server.listen();
    } catch (std::exception& e) {
        std::cout << "FATAL ERROR: " << e.what() << std::endl;
    }

    return 0;
}