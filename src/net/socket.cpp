#include "net/socket.h"

namespace loftili { 
  
namespace net {

// Socket Handle class
Socket::Socket () {
  m_ref = new Socket::SocketRef();
  m_ref->m_count = 1;
};

Socket::Socket(const Socket& other) {
  m_ref = other.m_ref;
  m_ref->m_count++;
};

Socket& Socket::operator=(const Socket& other) {
  if(--m_ref->m_count <= 0) delete m_ref;
  m_ref = other.m_ref;
  m_ref->m_count++;
  return *this;
};

bool Socket::Ok() {
  return m_ref->m_ok;
};

int Socket::Connect(const char *hostname, const int port, bool ssl) {
  int result = m_ref->Connect(hostname, port);
  return result;
};

int Socket::Write(const char *message, const int length) {
  int result = m_ref->Write(message, length);
  return result;
};

Socket& Socket::operator>>(loftili::lib::Stream& stream) {
  *m_ref >> stream;
  return *this;
};

Socket::~Socket() {
  if(--m_ref->m_count <= 0) delete m_ref;
};

/* 
 * SocketRef body class
 */
Socket::SocketRef::SocketRef() : m_count(0), m_ok(false) {
  m_socket = socket(AF_INET, SOCK_STREAM, 0);
};

Socket::SocketRef::~SocketRef() {
  if(m_socket) {
    printf("closing socket\n");
    close(m_socket);
  }
}

int Socket::SocketRef::Connect(const char *hostname, int port) {
  hostent *he = gethostbyname(hostname);
  sockaddr_in sa;

  if(he == NULL) { 
    m_ok = false; 
    return -1;
  }

  memset(&sa, 0, sizeof(sa));
  sa.sin_family = AF_INET;
  sa.sin_port = htons(port);
  sa.sin_addr.s_addr = *(long *)he->h_addr;

  int result = connect(m_socket, (sockaddr*)&sa, sizeof(sa));

  if(result < 0) {
    m_ok = false;
    return -1;
  }

  m_ok = true;

  return 1;
};

Socket::SocketRef& Socket::SocketRef::operator >>(loftili::lib::Stream& stream) {
  int size = 2048, received;
  std::string buffer(size, 0);

  received = recv(m_socket, &buffer[0], size - 1, 0);

  if(received < 0) {
    m_ok = false;
    printf("%s", strerror(errno));
  }

  stream << buffer.c_str();

  return *this;
};

int Socket::SocketRef::Write(const char *message, const int length) {
  int size = send(m_socket, message, length, 0);
  if(size != length) { m_ok = false; return -1; }
  return size;
};

} 

}
