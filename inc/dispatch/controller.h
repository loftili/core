#ifndef _LOFTILI_CONTROLLER_H
#define _LOFTILI_CONTROLLER_H

#include <string.h>
#include <iostream>
#include "loftili.h"
#include "auth/credentials.h"
#include "util/logger.h"
#include "util/loggable.h"
#include "util/options.h"
#include "communication/response.h"
#include "communication/request.h"
#include "communication/json.h"

namespace loftili {

enum CONTROLLER_METHOD {
  CONTROLLER_METHOD_MISSING = -1
};

class Controller : public Loggable {
  friend class RouteList;
  
  public:
    virtual ~Controller() {};
    virtual int respondTo(Request* req, Response* res);
    virtual void initialize(Credentials new_credentials, Options init_options);
    std::string name;

  protected:
    virtual std::string logName() { return "Controller"; }
    void missing(Response* res);

  protected:
    std::map<std::string, int> method_map;
    Logger* log;
    Credentials device_credentials;
    Options device_options;

};

}

#endif
