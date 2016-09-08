//
// Created by vladislav on 07.09.16.
//

#include "connection.hpp"

Connection::Connection(boost::asio::ip::tcp::socket tcpSocket, const RequestHandler& requestHandler,
                       std::function<void (ConnectionPtr)> abortedCallback)
        : requestHandler(requestHandler), tcpSocket(std::move(tcpSocket)),
          abortedCallback(abortedCallback), messageSize(0) {}

void Connection::read() {
    boost::system::error_code ec;
    size_t bytesRead = tcpSocket.read_some(boost::asio::buffer(buffer), ec);

    if (ec) {
        close();
        return;
    }

    if (messageSize == 0) {
        messageSize = tcpSocket.available();
        message.clear();
        message.insert(message.end(), buffer.begin(), buffer.begin() + bytesRead);
    } else {
        messageSize -= bytesRead;
    }

    if (messageSize == 0)
        handle_message(std::string(message.begin(), message.end()));

    read();
}

void Connection::write(const std::string& message) {
    tcpSocket.write_some(boost::asio::buffer(message));
}

void Connection::close() {
    tcpSocket.close();
    abortedCallback(shared_from_this());
}

void Connection::handle_message(const std::string& request) {
    requestHandler.handle_request(request, std::bind(&Connection::write, this, std::placeholders::_1));
    close();
}