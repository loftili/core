#ifndef _LOFTILI_API_REGISTRATION_H
#define _LOFTILI_API_REGISTRATION_H

#include "api.h"
#include "rapidjson/reader.h"
#include "lib/json_parser.h"
#include "net/http_request.h"
#include "net/http_response.h"
#include "net/http_client.h"

namespace loftili {

namespace api {

class Registration {
  friend class Parser;
  public:
    Registration() = default;
    Registration(const Registration&) = default;
    Registration& operator=(const Registration&) = default;
    ~Registration() = default;

    int Register();
    loftili::api::DeviceCredentials Credentials();

  private:
    std::string RegistrationUrl();
    bool m_ok;
    loftili::api::DeviceCredentials m_credentials;

    class Parser : public loftili::lib::JsonParser {
      public: 
        Parser(Registration*);
        bool String(const char*, size_t, bool);
        bool Key(const char*, size_t, bool);
        bool Uint(unsigned int);
      private:
        std::string m_current_key;
        Registration *m_registration;
    };
};

}

}


#endif
