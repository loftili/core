#ifndef _LOFTILI_API_REGISTRATION_H
#define _LOFTILI_API_REGISTRATION_H

#include "api.h"
#include "rapidjson/reader.h"
#include "lib/json_parser.h"
#include "net/request.h"
#include "net/response.h"
#include "net/response_stream.h"

namespace loftili {

namespace api {

class Registration {
  friend class Parser;
  public:
    Registration();
    ~Registration();
    int Register();
    loftili::api::DeviceCredentials Credentials();

  private:
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
