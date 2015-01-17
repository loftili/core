#ifndef _LOFTILI_STATE_RELAY_H
#define _LOFTILI_STATE_RELAY_H

#include "loftili.h"
#include "util/logger.h"
#include "communication/json.h"
#include "communication/request.h"
#include "communication/response.h"
using namespace std;

namespace loftili {

class StateRelay {

  public:
    StateRelay();
    ~StateRelay();

    void send(string key, int state);

  private:
    Logger* log;

};

}

#endif
