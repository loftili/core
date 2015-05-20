#include "net/tcp_socket.h"

namespace loftili {

namespace net {

TcpSocket::TcpSocket() : m_impl(new impl::Impl()) {
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
