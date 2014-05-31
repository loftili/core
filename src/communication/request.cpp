#include "communication/request.h"

namespace loftili {

Request::Request(std::string u, std::string m) : url(u), method(m){
}

Request::~Request() {
}

}
