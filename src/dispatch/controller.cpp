#include "dispatch/controller.h"

namespace loftili {

void Controller::initialize(Credentials init_credentials, Options init_options) {  
  device_options = init_options;
  device_credentials = init_credentials;
  log = new Logger(logName());
}

void Controller::missing(Response* res) {
  res->status = 404;
}

int Controller::respondTo(Request* request, Response* response) {
  log->info("responding via Controller base class");
  std::stringstream ss;
  ss << "url: " << request->url;
  log->info(ss.str());

  if(request->c_method == CONTROLLER_METHOD_MISSING)
    response->status = HTTP_NOT_FOUND;

  return 0;
}

}
