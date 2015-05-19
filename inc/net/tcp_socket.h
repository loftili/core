#ifndef _LFTNET_TCP_SOCKET_H
#define _LFTNET_TCP_SOCKET_H

#include <iostream>
#include <memory>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

namespace loftili {

namespace net {

class TcpSocket {
  public:
    TcpSocket();
    ~TcpSocket();
    int Connect(const char *, int);
    int Write(const char *, int);
    int Read(char *, int);
  private:
    int m_handle;
};

}

}

#endif
