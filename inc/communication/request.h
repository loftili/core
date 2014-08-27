#ifndef _LOFTILI_REQUEST_H
#define _LOFTILI_REQUEST_H

#include <string>
#include <iostream>
#include <sstream>
#include "loftili.h"

namespace loftili {

struct Request {

  public:
    Request(std::string url, std::string method);
    ~Request();
    std::string url;
    std::string method;
    int c_method;

};

}

#endif
