#include "net/request.h"

namespace loftili {

namespace net {

Request::Request() : m_method("GET"), m_path(""), m_host("") {
}

Request::Request(string url) {
}

Request::Request(const Request& other) {
}

Request::~Request() {
}

Request& Request::operator=(const Request& other) {
  return *this;
}

}

}
