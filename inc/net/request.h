#ifndef _LOFTILI_NET_REQUEST_H
#define _LOFTILI_NET_REQUEST_H

#include <iostream>
#include <iterator>
#include <vector>
#include <string>
#include <sstream>
#include "net/response_stream.h"
#include "net/socket.h"
#include "net/url.h"

namespace loftili {

namespace net {

using namespace std;

class Request {
  public:
    Request();
    ~Request();
    Request(const Request&);
    Request& operator=(const Request&);

    Request(string);
    Request(Url);
    Request(string, string);
    Request(string, string, int, string);

    int Send(loftili::net::ResponseStream*);
    int Send(loftili::net::ResponseStream*, string);
    int Header(string, string);

  private:
    void ParseUrl(std::string);
    int Connect();
    int WriteOut(string);
    void Close();

    string m_method;
    string m_host;
    string m_path;
    vector<string> m_headers;
    int m_port;

    loftili::net::Socket *m_socket;
};

}

}


#endif
