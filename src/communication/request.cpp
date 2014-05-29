#include "communication/request.h"

namespace loftili {

Request::Request(string u, string m) : url(u), method(m){
}

Request::~Request() {
}

}
