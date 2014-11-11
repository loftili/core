#ifndef _LOFTILI_CREDENTIALS_H
#define _LOFTILI_CREDENTIALS_H

#include "loftili.h"

class Registration;

namespace loftili {

class Credentials {
  friend class Registration;

  public:
    Credentials();
    Credentials(std::string token);
    ~Credentials();
    bool valid();
    std::string token();
    int deviceId();

  private:
    void initialize(std::string new_token, int id);
    bool is_valid;
    std::string api_token;
    int device_id;

};

}

#endif
