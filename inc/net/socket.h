#ifndef _LOFTILI_NET_SOCKET_H
#define _LOFTILI_NET_SOCKET_H

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include <openssl/rand.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#include "lib/stream.h"

namespace loftili { 
  
namespace net {

class Socket {
  public:
    Socket();
    Socket(const Socket& other);
    Socket& operator=(const Socket& other);
    ~Socket();

    int Connect(const char*, int, bool);
    int Write(const char*, const int);
    int Reconnect();
    Socket& operator>>(loftili::lib::Stream&);
    bool Ok();

  private:
    class SocketRef {
      friend Socket;
      public:
        SocketRef();
        ~SocketRef();
        int Connect(const char*, int);
        int Write(const char*, int);
        int Reconnect();
        SocketRef& operator>>(loftili::lib::Stream&);
      private:
        std::string m_hostname;
        int m_port;
        int m_count;
        int m_socket;
        bool m_ok;
    };

    SocketRef* m_ref;
};

} 

}

#endif
