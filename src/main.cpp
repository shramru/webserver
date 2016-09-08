#include <iostream>
#include "server.hpp"

int main() {
    try {
        Server server("0.0.0.0", "8080", "/home/vladislav/web");
        server.listen();
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}