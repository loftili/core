#include "dispatch/controller.h"

namespace loftili {

void Controller::initialize() {  
  log = new Logger(logName());
}

void Controller::missing(Response* res) {
  res->status = 404;
}

int Controller::respondTo(Request* request, Response* response) {
  log->info("Responding via Controller base class");

  if(request->c_method == MISSING)
    response->status = HTTP_NOT_FOUND;

  return 0;
}

}
