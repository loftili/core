#ifndef _LOFTILI_API_H
#define _LOFTILI_API_H

#include <iostream>
#include "rapidjson/document.h"

#define LOFTILI_API_TOKEN_HEADER "x-loftili-device-token"
#define LOFTILI_API_SERIAL_HEADER "x-loftili-device-serial"

namespace loftili {

namespace api {

typedef rapidjson::UTF8<> JsonUtf8;
typedef rapidjson::GenericStringStream<JsonUtf8> JsonStream;

struct ApiConfiguration {
  std::string protocol = "https";
  std::string serial = "1111111111111111111111111111111111111111";
  std::string hostname = "127.0.0.1";
  int port = 1337;
};

struct DeviceCredentials {
  std::string token;
  int device_id;
};

extern loftili::api::ApiConfiguration configuration;

}

}

#endif
