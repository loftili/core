#ifndef _LOFTILI_CONTROLLER_H
#define _LOFTILI_CONTROLLER_H

#include <string.h>
#include <iostream>
#include "loftili.h"
#include "util/logger.h"
#include "util/loggable.h"
#include "communication/response.h"
#include "communication/request.h"

namespace loftili {

class Controller : public Loggable {
  friend class RouteList;
  
  public:
    virtual ~Controller() {};
    virtual int respondTo(Request* req, Response* res);
    void initialize();
    std::string name;

  protected:
    virtual std::string logName() { return "Controller"; }
    std::map<std::string, int> method_map;
    Logger* log;

};

}

#endif
