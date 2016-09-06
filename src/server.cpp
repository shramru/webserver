//
// Created by vladislav on 07.09.16.
//

#include "server.hpp"

Server::Server(const std::string &address, const std::string & port, const std::string &directory, size_t workers)
        : requestHandler(directory), threadPool(workers), tcpAcceptor(ioService), tcpSocket(ioService)  {
    bait::resolver resolver(ioService);
    bait::endpoint endpoint = *resolver.resolve({address, port});
    tcpAcceptor.open(endpoint.protocol());
    tcpAcceptor.bind(endpoint);
    tcpAcceptor.set_option(bait::acceptor::reuse_address(true));

}

void Server::listen() {
    boost::system::error_code ec;
    tcpAcceptor.accept(tcpSocket, ec);
    if (ec) {

        return;
    }

    ConnectionPtr connection = std::make_shared<Connection>(std::move(tcpSocket), requestHandler,
                                                            [this] (ConnectionPtr connectionPtr) {
                                                                connectedClients.erase(connectionPtr);
                                                            });
    connectedClients.insert(connection);

    threadPool.enqueue(std::bind(&Connection::read, &*connection));

    listen();
}
