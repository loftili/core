#ifndef _LOFTILI_NET_RESPONSE_H
#define _LOFTILI_NET_RESPONSE_H

#include "rapidjson/document.h"
#include <iostream>
#include <sstream>
#include <vector>

namespace loftili {

namespace net {

class Response {
  public:
    Response();
    Response(std::string headers, std::string body);
    Response(const Response&);
    Response& operator=(const Response&);
    ~Response();

    std::string Body() { return m_body; };
    int Code() { return m_code; };

  private:
    void ParseHead();
    void ParseStatusLine(std::string);

    int m_code;
    std::string m_body;
    std::string m_head;
    std::vector< std::pair<std::string, std::string> > m_headers;
};

}

}

#endif
