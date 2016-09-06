//
// Created by vladislav on 07.09.16.
//

#ifndef WEBSERVER_CONNECTION_HPP
#define WEBSERVER_CONNECTION_HPP

#include <boost/asio.hpp>
#include "request_handler.hpp"

class Connection {

    using bait = boost::asio::ip::tcp;

    bait::socket tcpSocket;
    RequestHandler requestHandler;
    std::function<void (std::shared_ptr<Connection>)> abortedCallback;

public:

    void read();
    void write();

    Connection(const bait::socket tcpSocket, const RequestHandler& requestHandler,
               std::function<void (std::shared_ptr<Connection>)> abortedCallback);
};

typedef std::shared_ptr<Connection> ConnectionPtr;

#endif //WEBSERVER_CONNECTION_HPP
