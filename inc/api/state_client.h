#ifndef _LOFTILI_API_STATE_CLIENT_H
#define _LOFTILI_API_STATE_CLIENT_H

#include "config.h"
#include "api.h"
#include "spdlog/spdlog.h"
#include "rapidjson/reader.h"
#include "lib/json_parser.h"
#include "net/http_request.h"
#include "net/http_response.h"
#include "net/http_client.h"

namespace loftili {

namespace api  {

class StateClient {
  public:
    StateClient() = default;
    StateClient(const StateClient&) = default;
    StateClient& operator=(const StateClient&) = default;
    ~StateClient() = default;
    void Update(std::string, int);

  private:
    std::string StateUrl();
};

}

}


#endif
