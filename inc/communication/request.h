#ifndef _RASBEAT_REQUEST_H
#define _RASBEAT_REQUEST_H

#include <iostream>

namespace rasbeat {

struct Request {

  public:
    Request(std::string url, std::string method);
    ~Request();

    std::string url;
    std::string method;

};

}

#endif
