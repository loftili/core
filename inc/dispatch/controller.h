#ifndef _LOFTILI_CONTROLLER_H
#define _LOFTILI_CONTROLLER_H

#include <string.h>
#include <iostream>
#include "util/logger.h"
#include "communication/response.h"
#include "communication/request.h"

namespace loftili {

class Controller {
  
public:
  Controller();
  virtual ~Controller() {};
  virtual Response* respondTo(Request* r);
  virtual void initialize() = 0;

  std::string name;

protected:
  Logger* log;

};

}

#endif
