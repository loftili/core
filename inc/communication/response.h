#ifndef _LOFTILI_RESPONSE_H
#define _LOFTILI_RESPONSE_H

#include <cstring>
#include <sstream>
#include "loftili.h"

namespace loftili {

class Response {

  public:
    Response();
    Response(int _status);
    ~Response();
    void json(std::string key, std::string value);

  private:
    void setDefaultHeaders();

  public:
    int length;
    void* content;
    int status;
    HttpHeaders headers;
    ControllerMethod c_method;

};

}

#endif
