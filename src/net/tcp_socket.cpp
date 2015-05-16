#include "net/tcp_socket.h"

namespace loftili {

namespace net {

TcpSocket::TcpSocket() : m_handle(socket(AF_INET, SOCK_STREAM, 0)) { };

TcpSocket::~TcpSocket() {
  close(m_handle);
}

int TcpSocket::Connect(const char *hostname, int port) {
  hostent *he = gethostbyname(hostname);
  sockaddr_in sa;

  if(he == NULL)
    return -1;

  memset(&sa, 0, sizeof(sa));
  sa.sin_family = AF_INET;
  sa.sin_port = htons(port);
  sa.sin_addr.s_addr = *(long *)he->h_addr;

  return connect(m_handle, (sockaddr*)&sa, sizeof(sa));
};

int TcpSocket::Write(const char *data, int size) {
  return send(m_handle, data, size, 0);
};

int TcpSocket::Read(char *data, int size) {
  return recv(m_handle, data, size, 0);
};

}

}
