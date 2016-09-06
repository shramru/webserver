//
// Created by vladislav on 07.09.16.
//

#ifndef WEBSERVER_REQUEST_HANDLER_HPP
#define WEBSERVER_REQUEST_HANDLER_HPP

#include <string>

class RequestHandler {

    std::string root_dir;

public:

    RequestHandler(const std::string& dir);
};


#endif //WEBSERVER_REQUEST_HANDLER_HPP
