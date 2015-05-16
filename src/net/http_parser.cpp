#include "net/http_parser.h"

namespace loftili {

namespace net {

HttpParser::HttpParser() : m_impl(new loftili::net::HttpParser::Impl) {
}

bool HttpParser::operator<<(loftili::net::TcpSocket& socket) {
  do {
    m_impl->Read(socket);
  } while(m_impl->Receiving());

  return m_impl->m_state == loftili::net::HttpParser::Impl::RECEIVING_STATE_FINISHED;
}

HttpParser::Impl::Impl() : m_size(0), m_state(RECEIVING_STATE_HEADERS) {
  m_data = (char*) malloc(sizeof(char) * 1);
  m_data[0] = '\0';
}

HttpParser::Impl::~Impl() {
  free(m_data);
}

void HttpParser::Impl::Read(loftili::net::TcpSocket& socket) {
  char buffer[2048];

  int received = socket.Read(buffer, 2048);

  if(received < 0) {
    m_state = RECEIVING_STATE_ERRORED;
    return;
  }

  m_data = (char*) realloc(m_data, sizeof(char) * (received + m_size + 1));
  memcpy(&m_data[m_size], &buffer[0], sizeof(char) * received);
  m_size += received;
  m_data[m_size] = '\0';
  UpdateState();
}

void HttpParser::Impl::UpdateState() {
  char *header_break = strstr(m_data, "\r\n\r\n");

  if(header_break == nullptr)
    return;

  int header_end = header_break - m_data;

  if(header_end < 15) {
    m_state = RECEIVING_STATE_ERRORED;
    return;
  }

  bool headers = m_state == RECEIVING_STATE_HEADERS;

  if(headers) {
    FindContentLength();
    return;
  }

  if(m_size - (header_end + 4) == m_content_size)
    m_state = RECEIVING_STATE_FINISHED;
}

void HttpParser::Impl::FindContentLength() {
  char *header_break = strstr(m_data, "\r\n\r\n");

  if(header_break == nullptr)
    return;

  int header_end = header_break - m_data;
  std::stringstream header_reader(std::string(m_data, header_end));
  std::string line;
  while(std::getline(header_reader, line) && line != "\r") {
    int split = line.find(':', 0);

    if(split > line.size()  - 2 || split == 0)
      continue;

    std::string key = line.substr(0, split),
                val = line.substr(split + 2);

    if(key.find("Content-Length") == 0 && key.size() == 14) {
      m_content_size = std::stoi(val);
      m_state = RECEIVING_STATE_BODY;
      UpdateState();
    }
  }
}

bool HttpParser::Impl::Receiving() {
  return m_state != RECEIVING_STATE_ERRORED && m_state != RECEIVING_STATE_FINISHED;
}

}

}
