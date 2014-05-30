#include "dispatch/controller.h"

namespace loftili {

Controller::Controller() {  }

Response* Controller::respondTo(Request* request) {
  std::cout << name << " is responding via base class" << std::endl;
  Response* r;
  return r;
}

}
