#include "dispatch/controllers/root.h"

namespace loftili {

RootController::RootController() {
  name = "RootController";
}

RootController::~RootController() {
  delete log;
}

}
