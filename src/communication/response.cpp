#include "communication/response.h"

namespace loftili {

Response::Response() : length(LOFTILI_EMPTY_RESPONSE_LEN), status(200) {
  size_t realsize = sizeof(char) * length;
  content = malloc(realsize);
  memcpy(content, LOFTILI_EMPTY_RESPONSE, realsize);
  setDefaultHeaders();
}

Response::Response(std::string con, int len) : length(len) {
  size_t realsize = sizeof(char) * length;
  content = malloc(realsize);
  memcpy(content, con.c_str(), realsize);
  setDefaultHeaders();
}

Response::Response(int _status) : length(LOFTILI_EMPTY_RESPONSE_LEN), status(_status) {
  size_t realsize = sizeof(char) * length;
  content = malloc(realsize);
  memcpy(content, LOFTILI_EMPTY_RESPONSE, realsize);
  setDefaultHeaders();
}

Response::~Response() {
  if(content != NULL)
    free(content);
}

void Response::setDefaultHeaders() {
  headers.insert(HttpHeader(HEADER_CONTENT_TYPE, "application/json"));
  headers.insert(HttpHeader(HEADER_LOFTILI_VERSION, PACKAGE_VERSION));
}

void Response::json(Json* doc) {
  char* doc_str = doc->buffer();
  int len = strlen(doc_str);
  size_t realsize = sizeof(char) * len;
  content = realloc(content, len + 1);
  memcpy(content, doc_str, realsize);
  length = len;
}

}
