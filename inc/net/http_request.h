#ifndef _LFTNET_HTTP_REQUEST_H
#define _LFTNET_HTTP_REQUEST_H

#include <vector>
#include <iostream>
#include <sstream>
#include "net/url.h"
#include "net/tcp_socket.h"

namespace loftili {

namespace net {

class HttpRequest {
  public:
    HttpRequest(const HttpRequest&) = default;
    HttpRequest& operator=(const HttpRequest&) = default;
    ~HttpRequest() = default;

    HttpRequest(const Url&);
    HttpRequest(const Url&, std::string);
    HttpRequest(const Url&, std::string, std::string);
    int Header(std::string, std::string);
    operator std::string();
    const loftili::net::Url& Url() { return m_url; }

  private:
    loftili::net::Url m_url;
    std::string m_method;
    std::string m_body;
    std::vector< std::pair<std::string, std::string> > m_headers;
};

}

}

#endif
