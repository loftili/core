#include "communication/response.h"

namespace loftili {

Response::Response() : length(LOFTILI_EMPTY_RESPONSE_LEN), status(200) {
  content = (void*) malloc(LOFTILI_EMPTY_RESPONSE_LEN * sizeof(char));
  memcpy(content, LOFTILI_EMPTY_RESPONSE, LOFTILI_EMPTY_RESPONSE_LEN * sizeof(char));
}

Response::Response(int _status) : length(LOFTILI_EMPTY_RESPONSE_LEN), status(_status) {
  content = (void*) malloc(LOFTILI_EMPTY_RESPONSE_LEN * sizeof(char));
  memcpy(content, LOFTILI_EMPTY_RESPONSE, LOFTILI_EMPTY_RESPONSE_LEN * sizeof(char));
}

void Response::json(void) {
  status = 200;
}

void Response::json(ShallowJson* json) {
  std::string out = "[";
  for(ShallowJson::iterator it = json->begin(); it != json->end(); ++it)
    out += "{\"" + it->first + "\":\"" + it->second + "\"}";
  out += "]";

  length = strlen(out.c_str());
  content = (void*) malloc(length * sizeof(char));
  memcpy(content, out.c_str(), length * sizeof(char));
  status = 200;
}

Response::~Response() {
  if(content)
    free(content);
} 

}
