#include "communication/response.h"

namespace loftili {

Response::Response() : length(LOFTILI_EMPTY_RESPONSE_LEN), status(200) {
  content = (void*)LOFTILI_EMPTY_RESPONSE;
  setDefaultHeaders();
}

Response::Response(int _status) : length(LOFTILI_EMPTY_RESPONSE_LEN), status(_status) {
  content = (void*)LOFTILI_EMPTY_RESPONSE;
  setDefaultHeaders();
}

void Response::setDefaultHeaders() {
  headers.insert(HttpHeader(HEADER_CONTENT_TYPE, "application/json"));
  headers.insert(HttpHeader(HEADER_LOFTILI_VERSION, PACKAGE_VERSION));
}

void Response::json(void) {
  status = 200;
}

Response::~Response() { } 

}
