#include <iostream>
#include "server.hpp"

int main() {
    try {
        Server server("0.0.0.0", "8080", "/home/vladislav");
        server.listen();
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}