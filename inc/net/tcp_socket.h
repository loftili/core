#ifndef _LFTNET_TCP_SOCKET_H
#define _LFTNET_TCP_SOCKET_H

#if defined(__APPLE__)
#define APPLE 1
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#else
#define APPLE 0
#endif


#include <openssl/rand.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <memory.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <memory>
#include <iostream>
#include <errno.h>

namespace loftili {

namespace net {

namespace impl { struct Derived{}; }

class TcpSocket {
  public:
    TcpSocket();
    TcpSocket(bool);
    TcpSocket(impl::Derived);
    TcpSocket& operator=(const TcpSocket&);
    TcpSocket(const TcpSocket&);
    virtual ~TcpSocket();
    virtual int Connect(const char *, int);
    virtual int Write(const char *, int);
    virtual int Read(char *, int);
  protected:
    int m_refcount;
    TcpSocket *m_impl;
};

namespace impl {

class SslImpl : public TcpSocket {
  public:
    SslImpl();
    ~SslImpl();
    int Connect(const char *, int);
    int Write(const char *, int);
    int Read(char *, int);
  private:
    int m_handle;
    SSL *m_ssl;
    SSL_CTX *m_context;
};

class Impl : public TcpSocket {
  public:
    Impl();
    ~Impl();
    int Connect(const char *, int);
    int Write(const char *, int);
    int Read(char *, int);
  private:
    int m_handle;
};

}

}

}

#endif
