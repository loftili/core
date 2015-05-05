#include "net/response.h"

namespace loftili {

namespace net {

Response::Response() : m_head(""), m_body(""), m_code(-1) {
}

Response::Response(std::string head, std::string body) : m_head(head), m_body(body) {
  ParseHead();
};

Response::~Response() {
};

Response::Response(const Response& other) {
  m_head = other.m_head;
  m_body = other.m_body;
  m_code = other.m_code;
  ParseHead();
};

Response& Response::operator=(const Response& other) {
  m_head = other.m_head;
  m_body = other.m_body;
  m_code = other.m_code;
  ParseHead();
  return *this;
};

void Response::ParseHead() {
  std::istringstream head_stream(m_head);
  std::string header;
  int line = 0;

  while(std::getline(head_stream, header) && header != "\r") {
    int index = header.find(':', 0);

    if(line++ == 0)
      ParseStatusLine(header);

    if(index < 0) continue;

    std::string key = header.substr(0, index),
                value = header.substr(index + 2);

    m_headers.push_back(
      std::make_pair<std::string, std::string>(
        header.substr(0, index),
        header.substr(index + 2)
      )
    );
  }
}

void Response::ParseStatusLine(std::string line) {
  int index, group = -1;

  while((index = line.find(' ')) >= 0 && ++group < 3) {
    std::string current = line.substr(0, index);

    if(group == 1) 
      m_code = std::stoi(current);

    line = line.substr(index + 1);
  }
}

}

}
