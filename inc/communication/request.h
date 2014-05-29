#ifndef _LOFTILI_REQUEST_H
#define _LOFTILI_REQUEST_H

#include <iostream>
using namespace std;

namespace loftili {

struct Request {

  public:
    Request(string url, string method);
    ~Request();
    string url;
    string method;

};

}

#endif
