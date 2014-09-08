#include "communication/response.h"

namespace loftili {

Response::Response() : length(LOFTILI_EMPTY_RESPONSE_LEN), status(200) {
  size_t realsize = sizeof(char) * length;
  content = malloc(realsize);
  memcpy(content, LOFTILI_EMPTY_RESPONSE, realsize);
  setDefaultHeaders();
}

Response::~Response() {
  if(content != NULL)
    free(content);
}

Response::Response(std::string con, int len) : length(len) {
  content = malloc(sizeof(char) * length);
  size_t realsize = sizeof(char) * length;
  memcpy(content, con.c_str(), realsize);
}

Response::Response(int _status) : length(LOFTILI_EMPTY_RESPONSE_LEN), status(_status) {
  size_t realsize = sizeof(char) * length;
  content = malloc(realsize);
  memcpy(content, LOFTILI_EMPTY_RESPONSE, realsize);
  setDefaultHeaders();
}

void Response::setDefaultHeaders() {
  headers.insert(HttpHeader(HEADER_CONTENT_TYPE, "application/json"));
  headers.insert(HttpHeader(HEADER_LOFTILI_VERSION, PACKAGE_VERSION));
}

void Response::json(Json* doc) { }

}
