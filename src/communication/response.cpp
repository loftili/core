#include "communication/response.h"

namespace rasbeat {

Response::Response() : length(RASB_EMPTY_RESPONSE_LEN), status(200) {
  content = (void*)RASB_EMPTY_RESPONSE;
}

Response::Response(int _status) : length(RASB_EMPTY_RESPONSE_LEN), status(_status) {
  content = (void*)RASB_EMPTY_RESPONSE;
}

Response::~Response() {
} 

}
