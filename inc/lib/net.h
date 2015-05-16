#ifndef _LOFTILI_LIB_NET_H
#define _LOFTILI_LIB_NET_H

#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <netdb.h>

namespace loftili {

namespace lib {

namespace net {

template <class TT_SocketManager>
class T_Socket : public TT_SocketManager {
  public:
    T_Socket() : TT_SocketManager() { };
    ~T_Socket() = default;

    template <class TT_Reader>
    T_Socket& operator >>(TT_Reader& reader) {
      const int size = 2048;
      char *buffer = new char[size];
      int received = TT_SocketManager::Read(buffer, size);
      buffer[size - 1] = '\0';
      reader << buffer;
      delete buffer;
      return *this;
    };
};

}

}

}

#endif
