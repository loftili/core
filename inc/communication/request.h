#ifndef _RASBEAT_REQUEST_H
#define _RASBEAT_REQUEST_H

#include <iostream>
using namespace std;

namespace rasbeat {

struct Request {

  public:
    Request(string url, string method);
    ~Request();
    string url;
    string method;

};

}

#endif
