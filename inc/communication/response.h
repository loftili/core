#ifndef _RASBEAT_RESPONSE_H
#define _RASBEAT_RESPONSE_H

#include "../rasbeat.h"

namespace rasbeat {

class Response {

  public:
    Response();
    Response(int _status);
    ~Response();

    int length;
    void* content;
    int status;

};

}

#endif
