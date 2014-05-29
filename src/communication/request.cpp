#include "../../inc/communication/request.h"

namespace rasbeat {

Request::Request(std::string _url, std::string _method) {
  url = _url;
  method = _method;
}

Request::~Request() {
}

}
