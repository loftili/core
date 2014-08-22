#ifndef _LOFTILI_RESPONSE_H
#define _LOFTILI_RESPONSE_H

#define LOFTILI_EMPTY_RESPONSE "<html><head></head><body></body></html>"
#define LOFTILI_EMPTY_RESPONSE_LEN strlen(LOFTILI_EMPTY_RESPONSE)

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
