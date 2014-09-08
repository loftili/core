#ifndef _LOFTILI_RESPONSE_H
#define _LOFTILI_RESPONSE_H

#include <cstring>
#include <sstream>
#include "loftili.h"
#include "communication/json.h"

namespace loftili {

class Response {

  public:
    Response();
    Response(int _status);
    Response(std::string con, int len);
    ~Response();
    void json(Json* doc);

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
