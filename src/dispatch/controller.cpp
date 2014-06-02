#include "dispatch/controller.h"

namespace loftili {

void Controller::initialize() {  
  log = new Logger(logName());
}

Response* Controller::respondTo(Request* request) {
  log->info("Responding via Controller base class");
  Response* r;
  return r;
}

}
