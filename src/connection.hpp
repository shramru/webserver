//
// Created by vladislav on 07.09.16.
//

#ifndef WEBSERVER_CONNECTION_HPP
#define WEBSERVER_CONNECTION_HPP

#include <boost/asio.hpp>
#include "request_handler.hpp"

class Connection
        : public std::enable_shared_from_this<Connection> {
    using bait = boost::asio::ip::tcp;

    bait::socket tcpSocket;
    RequestHandler requestHandler;
    std::function<void (std::shared_ptr<Connection>)> abortedCallback;

    static const int BUFFER_SIZE = 8192;
    std::array<char, BUFFER_SIZE> buffer;
    size_t messageSize;
    std::vector<char> message;

    void handle_message(const std::vector<char>& newMessage);

public:
    void read();
    void write(const std::vector<char>& message);
    void close();

    Connection(const bait::socket tcpSocket, const RequestHandler& requestHandler,
               std::function<void (std::shared_ptr<Connection>)> abortedCallback);
};

typedef std::shared_ptr<Connection> ConnectionPtr;

#endif //WEBSERVER_CONNECTION_HPP
