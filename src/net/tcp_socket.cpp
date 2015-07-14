#include "net/tcp_socket.h"

namespace loftili {

namespace net {

TcpSocket::TcpSocket() : m_impl(new impl::Impl()) {
  m_impl->m_refcount++;
}

TcpSocket::TcpSocket(bool is_ssl) {
  if(is_ssl)
    m_impl = new impl::SslImpl();
  else
    m_impl = new impl::Impl();

  m_impl->m_refcount++;
}

TcpSocket::TcpSocket(impl::Derived) : m_refcount(0), m_impl(0) {
};

TcpSocket::~TcpSocket() {
  if(m_impl != 0 && --m_impl->m_refcount <= 0) delete m_impl;
}

TcpSocket::TcpSocket(const TcpSocket& other) {
  m_impl = other.m_impl;
  m_impl->m_refcount++;
}

TcpSocket& TcpSocket::operator=(const TcpSocket& other) {
  if(m_impl != 0 && --m_impl->m_refcount <= 0) delete m_impl;
  m_impl = other.m_impl;
  m_impl->m_refcount++;
  return *this;
}

int TcpSocket::Connect(const char *hostname, int port) {
  int result = m_impl != 0 ? m_impl->Connect(hostname, port) : -1;
  return result;
};

int TcpSocket::Write(const char *data, int size) {
  return m_impl != 0 ? m_impl->Write(data, size) : -1;
};

int TcpSocket::Read(char *data, int size) {
  return m_impl != 0 ? m_impl->Read(data, size) : -1;
};

namespace impl {

SslImpl::SslImpl() : TcpSocket(Derived()), m_handle(socket(AF_INET, SOCK_STREAM, 0)), m_context(0) {
  SSL_load_error_strings();
  SSL_library_init();
  m_context = SSL_CTX_new(SSLv23_client_method());
  m_ssl = SSL_new(m_context);
}

SslImpl::~SslImpl() {
  close(m_handle);
  SSL_shutdown(m_ssl);
  SSL_free(m_ssl);
  SSL_CTX_free(m_context);
}

int SslImpl::Connect(const char *hostname, int port) {
  hostent *he = gethostbyname(hostname);
  sockaddr_in sa;

  if(he == NULL) return -1;

  memset(&sa, 0, sizeof(sa));
  sa.sin_family = AF_INET;
  sa.sin_port = htons(port);
  sa.sin_addr.s_addr = *(long *)he->h_addr;

  int result = connect(m_handle, (sockaddr*)&sa, sizeof(sa));

  if(result < 0) 
    return result;

  if(!SSL_set_fd(m_ssl, m_handle)) {
    printf("failed converting to ssl\n");
    return -1;
  }

  if(SSL_connect(m_ssl) != 1) {
    printf("failed connecting\n");
    return -1;
  }

  return result;
}

int SslImpl::Read(char *buffer, int size) {
  return SSL_read(m_ssl, buffer, size);
}

int SslImpl::Write(const char *data, int size) {
  return SSL_write(m_ssl, std::string(data, size).c_str(), size);
}

Impl::Impl() : TcpSocket(Derived()), m_handle(socket(AF_INET, SOCK_STREAM, 0)) {
}

int Impl::Connect(const char *hostname, int port) {
  int result;
  struct hostent *host;
  struct sockaddr_in server;
  host = gethostbyname(hostname);
  server.sin_family = AF_INET;
  server.sin_port = htons(port);
  server.sin_addr = *((struct in_addr *) host->h_addr);
  bzero (&(server.sin_zero), 8);
  result = connect(m_handle, (struct sockaddr *) &server, sizeof (struct sockaddr));
  return result;
};

int Impl::Write(const char *data, int size) {
  int result = send(m_handle, std::string(data, size).c_str(), size, 0);

  if(result < 0)
    printf("attempted [%d] but sent [%d] [%s]", size, result, strerror(errno));

  return result;
}

int Impl::Read(char *buffer, int size) {
  return recv(m_handle, buffer, size, 0);
}

Impl::~Impl() {
  close(m_handle);
}

}


}

}
