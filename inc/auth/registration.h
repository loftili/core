#ifndef _LOFTILI_REGISTRATION_H
#define _LOFTILI_REGISTRATION_H

#include "loftili.h"
#include "util/logger.h"
#include "util/options.h"
#include "auth/credentials.h"
#include "communication/request.h"
#include "communication/json.h"

namespace loftili {

class Registration {

  public:
    Registration(Options opts);
    bool attempt();
    Credentials creds();
    Options opts();
    Logger log;

  private:
    std::string endpoint();
    Options options;
    Credentials current_credentials;

  public:
    static size_t receiver(char *ptr, size_t size, size_t nmemb, void *userdata);

};

}

#endif
