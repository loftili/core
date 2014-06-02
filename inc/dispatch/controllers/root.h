#ifndef _LOFTILI_ROOT_CONTROLLER_H
#define _LOFTILI_ROOT_CONTROLLER_H

#include "dispatch/controller.h"

namespace loftili {

class RootController : public Controller {

public:
  RootController();
  ~RootController();

protected:
  std::string logName() { return "RootController"; }

};

}

#endif
