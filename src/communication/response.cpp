#include "communication/response.h"

namespace loftili {

Response::Response() : length(LOFTILI_EMPTY_RESPONSE_LEN), status(200) {
  content = (void*)LOFTILI_EMPTY_RESPONSE;
}

Response::Response(int _status) : length(LOFTILI_EMPTY_RESPONSE_LEN), status(_status) {
  content = (void*)LOFTILI_EMPTY_RESPONSE;
}

Response::~Response() {
} 

}
