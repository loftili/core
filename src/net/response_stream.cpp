#include "net/response_stream.h"

namespace loftili {

namespace net {

ResponseStream& ResponseStream::operator <<(const char* data) {
  m_data << data;
  return *this;
};

bool ResponseStream::Finished() {
  std::string so_far = m_data.str();
  int body_start = so_far.find("\r\n\r\n");

  if(!m_has_headers && body_start > 0)
    m_has_headers = true;

  if(m_has_headers) {
    std::string point = so_far.substr(0, body_start);
    std::string status, content_length;

    int indx,
        line_no = 0;

    while((indx = point.find('\n')) >= 0 && point.size() > 0) {
      std::string line = point.substr(0, indx);

      if(line_no == 0) status = line.substr(line.find(' ')+1, 3);


      point = point.substr(indx+1, std::string::npos);

      if(line.find("Content-Length:") == 0)
        content_length = line.substr(line.find(':')+1, std::string::npos);

      line_no++;
    }

    if(content_length.size() > 0) m_content_length = std::stoi(content_length);
  }

  if(m_has_headers && m_content_length < 0) {
    printf("headers received and no content length \n");
    return true;
  }

  if(m_content_length >= 0 && body_start > 0) {
    std::string perceived_body = m_data.str().substr(body_start+4, std::string::npos);
    return perceived_body.size() == m_content_length;
  }

  return false;
}

}

}
