#ifndef _LOFTILI_REGISTRATION_SERVICE_h
#define _LOFTILI_REGISTRATION_SERVICE_h

#include "loftili.h"
#include "util/logger.h"
#include "communication/request.h"
#include "communication/response.h"
#include "communication/json.h"
using namespace std;

namespace loftili {

class RegistrationService {

  public:
    RegistrationService();
    ~RegistrationService();

    bool authenticate(Configuration* config);
};

}

#endif
