#ifndef _LOFTILI_RESPONSE_H
#define _LOFTILI_RESPONSE_H

#include "../loftili.h"

namespace loftili {

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
