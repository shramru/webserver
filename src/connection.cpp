//
// Created by vladislav on 07.09.16.
//

#include "connection.hpp"

Connection::Connection(boost::asio::ip::tcp::socket tcpSocket, const RequestHandler &requestHandler,
                       std::function<void (ConnectionPtr)> abortedCallback)
        : tcpSocket(std::move(tcpSocket)), requestHandler(requestHandler),
          abortedCallback(abortedCallback), messageSize(0) {

}

void Connection::read() {
    boost::system::error_code ec;
    size_t bytesRead = tcpSocket.read_some(boost::asio::buffer(buffer), ec);

    if (ec) {
        close();
        abortedCallback(shared_from_this());
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
        handle_message(message);

    read();
}

void Connection::write(const std::vector<char> &message) {
    tcpSocket.write_some(boost::asio::buffer(message));
}

void Connection::close() {
    tcpSocket.close();
}

void Connection::handle_message(const std::vector<char>& newMessage) {
    std::string request(newMessage.begin(), newMessage.end());
    std::string response;
    requestHandler.handle_request(request, response);
    write(std::vector<char>(response.begin(), response.end()));
}