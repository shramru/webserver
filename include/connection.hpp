//
// Created by vladislav on 07.09.16.
//

#ifndef WEBSERVER_CONNECTION_HPP
#define WEBSERVER_CONNECTION_HPP

#include <boost/asio.hpp>
#include <functional>
#include "request_handler.hpp"

class Connection
        : public std::enable_shared_from_this<Connection> {
    using bait = boost::asio::ip::tcp;

    RequestHandler requestHandler;
    bait::socket tcpSocket;
    std::function<void (std::shared_ptr<Connection>)> abortedCallback;

    static const int BUFFER_SIZE = 8192;
    std::array<char, BUFFER_SIZE> buffer;
    size_t messageSize;
    std::vector<char> message;

    void handle_message(const std::string& request);

public:
    void read();
    void write(const std::string& message);
    void close();

    Connection(const bait::socket tcpSocket, const RequestHandler& requestHandler,
               std::function<void (std::shared_ptr<Connection>)> abortedCallback);
};

typedef std::shared_ptr<Connection> ConnectionPtr;

#endif //WEBSERVER_CONNECTION_HPP
