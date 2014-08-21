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

  private:
    void setDefaultHeaders();

  public:
    int length;
    void* content;
    int status;
    HttpHeaders headers;

};

}

#endif
