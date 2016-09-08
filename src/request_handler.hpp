//
// Created by vladislav on 07.09.16.
//

#ifndef WEBSERVER_REQUEST_HANDLER_HPP
#define WEBSERVER_REQUEST_HANDLER_HPP

#include <string>
#include <unordered_map>

class RequestHandler {
    std::string root_dir;
    mutable std::unordered_map<std::string, std::string> ext_to_mime =
            {
                    { "html", "text/html" },
                    { "css", "text/css" },
                    { "js", "application/javascript" },
                    { "jpg", "image/jpeg" },
                    { "jpeg", "image/jpeg" },
                    { "png", "image/png" },
                    { "gif", "image/gif" },
                    { "swf", "application/x-shockwave-flash" }
            };

    std::string message_headers() const;
    std::string file_headers(size_t length, const std::string& ext) const;
    std::string get_extension(const std::string& url) const;
    bool is_directory(const std::string& path) const;
    bool get_file(const std::string& url, std::string& file) const;
    std::string get_code(int code) const;
    std::string build_response(const std::string& protocol, const std::string& code,
                               const std::string& headers, const std::string& body = std::string()) const;

public:
    void handle_request(const std::string& request, std::string& response) const;

    RequestHandler(const std::string& dir);
};


#endif //WEBSERVER_REQUEST_HANDLER_HPP
