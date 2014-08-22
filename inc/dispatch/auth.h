#ifndef _LOFTILI_AUTH_H
#define _LOFTILI_AUTH_H

namespace loftili {

class Auth { 

  public:
    Auth();
    ~Auth();
    bool validate(const char* auth_val);

};

}

#endif
