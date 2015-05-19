#ifndef _LFTNET_HTTP_CLIENT_H
#define _LFTNET_HTTP_CLIENT_H

#include <memory.h>
#include <vector>
#include "net/tcp_socket.h"
#include "net/http_request.h"
#include "net/http_parser.h"
#include "net/http_response.h"

namespace loftili {

namespace net {

class HttpClient {
  public:
    HttpClient() = default;
    HttpClient(const HttpClient&) = default;
    ~HttpClient() = default;
    HttpClient& operator=(const HttpClient&) = default;
    bool Send(HttpRequest&);
    std::shared_ptr<loftili::net::HttpResponse> Latest();
  private:
    loftili::net::HttpParser m_parser;
    std::vector< std::shared_ptr<loftili::net::HttpResponse> > m_responses;
};

}

}

#endif
