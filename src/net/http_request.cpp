#include "net/http_request.h"

namespace loftili {

namespace net {

HttpRequest::HttpRequest(const loftili::net::Url& url) 
  : m_url(url), m_method("GET") {
}

HttpRequest::HttpRequest(const loftili::net::Url& url, std::string method) 
  : m_url(url), m_method(method) {
}

HttpRequest::HttpRequest(const loftili::net::Url& url, std::string method, std::string body) 
  : m_url(url), m_method(method), m_body(body) {
}

HttpRequest::operator std::string() {
  std::stringstream req_str;
  req_str << m_method << " " << m_url.Path() << " HTTP/1.1\n";
  req_str << "Host: " << m_url.Host() << "\n";
  req_str << "Content-Length: " << m_body.size() << "\n";

  typedef std::pair<std::string, std::string> header_pairs;
  std::vector<header_pairs>::iterator it = m_headers.begin();
  for(; it != m_headers.end(); ++it) {
    req_str << std::get<0>(*it) << ": " << std::get<1>(*it) << "\n";
  }

  req_str << "X-Powered-By: loftili core";

  req_str << "\r\n\r\n";
  req_str << m_body;
  return req_str.str();
}

int HttpRequest::Header(std::string key, std::string val) {
  m_headers.push_back(std::make_pair(key, val));
  return m_headers.size();
}

}

}
