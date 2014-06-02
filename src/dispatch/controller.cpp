#include "dispatch/controller.h"

namespace loftili {

Controller::Controller() {  
  log = new Logger();
}

Response* Controller::respondTo(Request* request) {
  log->info("Responding via Controller base class");
  Response* r;
  return r;
}

}
