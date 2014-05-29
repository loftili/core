#include "../../inc/communication/response.h"

namespace rasbeat {

Response::Response() : length(10), status(200) {
  content = (void*)RASB_EMPTY_RESPONSE;
}

Response::Response(int _status) : length(10), status(_status) {
  content = (void*)RASB_EMPTY_RESPONSE;
}

Response::~Response() {
  std::cout << "in response cleanup" << std::endl;
} 

}
