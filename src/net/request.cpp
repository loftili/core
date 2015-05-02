#include "net/request.h"

namespace loftili {

namespace net {

Request::Request() : m_method("GET"), m_path(""), m_host("") {
}

Request::Request(string url) : m_method("GET") {
  printf("constructing connection info from: [%s]\n", url.c_str());
  ParseUrl(url);
}

Request::Request(string method, string url) : m_method(method) {
  ParseUrl(url);
}

Request::Request(string method, string hostname, int port, string path) : m_port(port), m_method(method), m_path(path), m_host(hostname) {
}

int Request::Send() {
  int ok;

  m_socket = new loftili::net::Socket();
  ok = m_socket->Connect(m_host.c_str(), m_port, false);

  if(ok < 0) {
    printf("failed connecting...\n");
    return -1;
  }

  std::stringstream r;
  r << m_method << " " << m_path << " HTTP/1.1\n";
  r << "Connection: Keep-alive\n\n";

  std::string http_req = r.str();
  loftili::net::ResponseStream *response = new loftili::net::ResponseStream();
  m_socket->Write(http_req.c_str(), http_req.size());

  do {
    (*m_socket) >> *((loftili::lib::Stream*) response);
  } while(!response->Finished() && m_socket->Ok());

  delete response;
  delete m_socket;

  m_socket = 0;

  return 0;
}

void Request::ParseUrl(std::string url) {
  // needed
};

Request::Request(const Request& other) {
}

Request::~Request() {
  if(m_socket) delete m_socket;
}

Request& Request::operator=(const Request& other) {
  return *this;
}

}

}
