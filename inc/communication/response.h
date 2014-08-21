#ifndef _LOFTILI_RESPONSE_H
#define _LOFTILI_RESPONSE_H

#include <cstring>
#include "loftili.h"

namespace loftili {

class Response {

  public:
    Response();
    Response(int _status);
    ~Response();
    void json(void);
    void json(ShallowJson* json);

  public:
    int length;
    void* content;
    int status;
    std::map<char,int> headers;

};

}

#endif
