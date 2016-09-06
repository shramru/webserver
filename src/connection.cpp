//
// Created by vladislav on 07.09.16.
//

#include "connection.hpp"

Connection::Connection(boost::asio::ip::tcp::socket tcpSocket, const RequestHandler &requestHandler,
                       std::function<void (ConnectionPtr)> abortedCallback)
        : tcpSocket(std::move(tcpSocket)), requestHandler(requestHandler), abortedCallback(abortedCallback) {

}

void Connection::read() {

}

void Connection::write() {

}
