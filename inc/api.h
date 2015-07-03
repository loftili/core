#ifndef _LOFTILI_API_H
#define _LOFTILI_API_H

#include <iostream>
#include "rapidjson/document.h"

#define LOFTILI_API_TOKEN_HEADER "x-loftili-device-token"
#define LOFTILI_API_SERIAL_HEADER "x-loftili-device-serial"
#define LOFTILI_API_PRODUCTION "https://api.loftili.com"

namespace loftili {

namespace api {

typedef rapidjson::UTF8<> JsonUtf8;
typedef rapidjson::GenericStringStream<JsonUtf8> JsonStream;

struct ApiConfiguration {
  std::string protocol;
  std::string serial;
  std::string hostname;
  int port;
};

struct DeviceCredentials {
  std::string token;
  int device_id;
};

extern loftili::api::ApiConfiguration configuration;
extern loftili::api::DeviceCredentials credentials;

}

}

#endif
