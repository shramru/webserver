//
// Created by vladislav on 07.09.16.
//

#include <fstream>
#include <sstream>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <sys/stat.h>
#include "request_handler.hpp"

RequestHandler::RequestHandler(const std::string &dir)
        : root_dir(dir) {}

void RequestHandler::handle_request(const std::string &request, std::string &response) const {
    std::istringstream iss(request);
    std::string method, url, protocol;
    iss >> method >> url >> protocol;

    std::string headers, body;
    int code;
    headers = message_headers();

    if (method == "GET") {
        if (get_file(url, body)) {
            headers += file_headers(body.size(), get_extension(url));
            code = 200;
        } else {
            code = 404; //todo content
        }
    } else if (method == "HEAD") {
        code = 200;
    } else if (method == "POST" || method == "PUT" || method == "PATCH" ||
               method == "DELETE" || method == "TRACE" || method == "CONNECT" ||
               method == "OPTIONS") {
        code = 405;
    } else {
        code = 501;
    }

    response = build_response(protocol, get_code(code), headers, body);
}

bool RequestHandler::is_directory(const std::string& path) const {
    struct stat s;
    return (stat(path.c_str(), &s) == 0) && (s.st_mode & S_IFDIR);
}

bool RequestHandler::get_file(const std::string &url, std::string &file) const {
    //todo переделать в мгновенное считывание и отправку
    std::string path = root_dir + url;
    if (is_directory(path))
        path += "index.html";

    std::ifstream in(path);
    if (!in.good()) return false;

    std::stringstream buffer;
    buffer << in.rdbuf();
    file = buffer.str();
    return true;
}

std::string RequestHandler::message_headers() const {
    std::ostringstream headers;
    headers.imbue(std::locale(headers.getloc(), new boost::posix_time::time_facet("%a, %d %b %Y %H:%M:%S GMT")));
    headers << "Server: HigloadWebServer/1.0 (Linux)\r\n"
            << "Date: " << boost::posix_time::second_clock::universal_time() << "\r\n"
            << "Connection: close\r\n";
    return headers.str();
}

std::string RequestHandler::file_headers(size_t length, const std::string& ext) const {
    std::ostringstream headers;
    headers << "Content-Length: " << length << "\r\n"
            << "Content-Type: " << ext_to_mime[ext] << "\r\n";
    return headers.str();
}

std::string RequestHandler::get_extension(const std::string &url) const {
    size_t pos = url.find_last_of('.');
    return (pos != std::string::npos) ? url.substr(pos + 1) : "html";
}

std::string RequestHandler::get_code(int code) const {
    switch (code) {
        case 200:
            return "200 OK";
        case 404:
            return "404 Not Found";
        case 405:
            return "405 Method Not Allowed";
        case 501:
            return "501 Not Implemented";
        default:
            return "";
    }
}

std::string RequestHandler::build_response(const std::string &protocol, const std::string &code,
                                           const std::string &headers, const std::string &body) const {
    std::stringstream response;
    response << protocol << ' ' << code << "\r\n" << headers << "\r\n" << body;
    return response.str();
}
