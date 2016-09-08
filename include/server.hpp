//
// Created by vladislav on 07.09.16.
//

#ifndef WEBSERVER_SERVER_HPP
#define WEBSERVER_SERVER_HPP

#include <boost/asio.hpp>
#include <thread>
#include <set>
#include "connection.hpp"
#include "threadpool.hpp"

class Server {
    using bait = boost::asio::ip::tcp;

    RequestHandler requestHandler;
    ThreadPool threadPool;

    boost::asio::io_service ioService;
    boost::asio::signal_set signalSet;
    bait::acceptor tcpAcceptor;
    bait::socket tcpSocket;

    std::set<ConnectionPtr> connectedClients;

public:
    void listen();
    void stop();

    Server(const std::string& address, const std::string & port, const std::string& directory,
           size_t workers = std::thread::hardware_concurrency());
    ~Server();
};


#endif //WEBSERVER_SERVER_HPP
