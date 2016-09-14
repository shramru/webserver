#include "server.hpp"

std::string currentDirectory(const char* path) {
    std::string dir = path;
    return dir.substr(0, dir.find_last_of('/'));
}

int main(int argc, char* argv[]) {
    std::string root_dir = currentDirectory(argv[0]);
    std::string port = "80";
    size_t workersMin = std::thread::hardware_concurrency();
    size_t workersMax = workersMin * 2;

    try {
        int c;
        while((c = getopt(argc, argv, "r:n:x:p:")) != -1) {
            switch (c) {
                case 'r':
                    root_dir = optarg;
                    break;
                case 'p':
                    port = optarg;
                    break;
                case 'n':
                    workersMin = (size_t)std::stoi(optarg);
                    break;
                case 'x':
                    workersMax = (size_t)std::stoi(optarg);
                    break;
                default:
                    throw std::invalid_argument("Unsupported flag");
            }
        }

        Server server("0.0.0.0", port, root_dir, workersMin, workersMax);
        server.listen();
    } catch (std::exception& e) {
        std::cout << "FATAL ERROR: " << e.what() << std::endl;
    }

    return 0;
}