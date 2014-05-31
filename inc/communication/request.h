#ifndef _LOFTILI_REQUEST_H
#define _LOFTILI_REQUEST_H

#include <iostream>

namespace loftili {

struct Request {

  public:
    Request(std::string url, std::string method);
    ~Request();
    std::string url;
    std::string method;

};

}

#endif
