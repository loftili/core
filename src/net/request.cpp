#include "net/request.h"

namespace loftili {

namespace net {

Request::Request() : m_method("GET"), m_path(""), m_host(""), m_socket(0) {
}

Request::Request(string url) : m_method("GET"), m_socket(0) { ParseUrl(url); }

Request::Request(string method, string url) : m_method(method), m_socket(0) { ParseUrl(url); }

Request::Request(string method, string hostname, int port, string path) : 
  m_port(port), m_method(method), m_path(path), m_host(hostname), m_socket(0) { };

int Request::Connect() {
  int ok;

  m_socket = new loftili::net::Socket();
  ok = m_socket->Connect(m_host.c_str(), m_port, false);

  if(ok < 0) {
    printf("failed connecting...\n");
    return -1;
  }

  return 0;
}

int Request::WriteOut(string body) {
  std::stringstream r;
  r << m_method << " " << m_path << " HTTP/1.1\n";
  r << "Connection: Keep-alive\n";
  r << "Content-Length: " << body.size() << "\n";

  for(auto it : m_headers) {
    r << it << "\n";
  }

  r << "\n";
  r << body << "\r\n";

  std::string http_req = r.str();
  m_socket->Write(http_req.c_str(), http_req.size());
  return 0;
}

int Request::Send(loftili::net::ResponseStream* stream, string body) {
  int ok = Connect();

  if(ok < 0) {
    printf("failed connecting...\n");
    return -1;
  }

  ok = WriteOut(body);

  do {
    (*m_socket) >> *((loftili::lib::Stream*) stream);
  } while(stream->Ok() && stream->Count() == 0 && m_socket->Ok());

  ok = m_socket->Ok() ? 0 : -1;

  Close();

  return ok;
}

int Request::Header(string key, string value) {
  m_headers.push_back(key + ": " + value);
  return m_headers.size();
}

int Request::Send(loftili::net::ResponseStream* stream) {
  int ok = Connect();

  if(ok < 0) {
    printf("failed connecting...\n");
    return -1;
  }

  ok = WriteOut("");

  do {
    (*m_socket) >> *((loftili::lib::Stream*) stream);
  } while(stream->Ok() && stream->Count() == 0 && m_socket->Ok());

  ok = m_socket->Ok() ? 0 : -1;

  Close();

  return ok;
}

void Request::Close() {
  delete m_socket;
  m_socket = 0;
}

void Request::ParseUrl(std::string url) {
  // needed
};

Request::Request(const Request& other) 
  : m_socket(0), m_method(other.m_method), m_path(other.m_path),
  m_headers(other.m_headers), m_port(other.m_port) { };

Request::~Request() {
  Close();
}

Request& Request::operator=(const Request& other) {
  m_port = other.m_port;
  m_host = other.m_host;
  m_method = other.m_method;
  m_headers = other.m_headers;
  m_path = other.m_path;
  return *this;
}

}

}
