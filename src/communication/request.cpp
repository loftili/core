#include "../../inc/communication/request.h"

namespace rasbeat {

Request::Request(string u, string m) : url(u), method(m){
}

Request::~Request() {
}

}
