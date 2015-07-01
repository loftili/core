#ifndef _LFTNET_HTTP_RESPONSE_H
#define _LFTNET_HTTP_RESPONSE_H

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

namespace loftili {

namespace net {

class HttpResponse {
  public:
    HttpResponse() = default;
    HttpResponse(const HttpResponse&) = default;
    HttpResponse& operator=(const HttpResponse&) = default;
    HttpResponse(const char*);
    ~HttpResponse() = default;
    const char* Body() { return m_body.data(); };
    int ContentLength() { return m_body.size(); }
    int Status() { return m_status; }
  private:
    std::vector< std::pair<std::string, std::string> > m_headers;
    std::vector<char> m_body;
    int m_status;
};

}

}

#endif
