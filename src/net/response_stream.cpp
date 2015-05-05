#include "net/response_stream.h"

namespace loftili {

namespace net {

ResponseStream& ResponseStream::operator <<(const char* data) {
  m_data << data;
  std::string so_far = m_data.str();
  int body_start = so_far.find("\r\n\r\n");

  if(body_start < 0) return *this;

  m_has_headers = true;

  if(m_content_length < 0) {
    std::string header_line;
    std::istringstream stream(so_far.substr(0, body_start));

    while(std::getline(stream, header_line) && header_line != "\r") {
      int split = header_line.find(':', 0);
      std::string key = header_line.substr(0, split),
                  val = header_line.substr(split + 2);

      if(key.find("Content-Length") == 0 && key.size() == 14)
        m_content_length = std::stoi(val);
    }

    if(m_content_length < 0) {
      m_ok = false;
      Reset();
    }
  }

  std::string body = so_far.substr(body_start + 4, std::string::npos);

  if(m_content_length >= 0 && body.size() == m_content_length) {
    m_responses.push_back(loftili::net::Response(so_far.substr(0, body_start), body));
    Reset();
  }

  return *this;
};

bool ResponseStream::operator >>(Response& response) {
  if(m_responses.size() < 1) return false;
  response = m_responses.back();
  m_responses.pop_back();
  return true;
}

void ResponseStream::Reset() {
  m_data.str("");
  m_content_length = -1;
  m_has_headers = false;
}

}

}
