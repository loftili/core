#include "auth/credentials.h"

namespace loftili {

Credentials::Credentials(std::string registered_token) {
  api_token = registered_token;
  is_valid = true;
}

Credentials::Credentials() : api_token(""), is_valid(false), device_id(-1) {
}

Credentials::~Credentials() {
}

void Credentials::initialize(std::string new_token, int id) {
  api_token = new_token;
  device_id = id;
  is_valid = true;
}

bool Credentials::valid() {
  return is_valid;
}

int Credentials::deviceId() {
  return device_id;
}

std::string Credentials::token() {
  return api_token;
}

}
