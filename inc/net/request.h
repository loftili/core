#ifndef _LOFTILI_NET_REQUEST_H
#define _LOFTILI_NET_REQUEST_H

#include "net/socket.h"

namespace loftili {

namespace net {

using namespace std;

class Request {
  public:
    Request();
    Request(string url);
    ~Request();
    Request(const Request&);
    Request& operator=(const Request&);

  private:
    string m_method;
    string m_host;
    string m_path;
    loftili::net::Socket *m_socket;
};

}

}


#endif
