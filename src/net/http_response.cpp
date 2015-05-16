#include "net/http_response.h"

namespace loftili {

namespace net {

HttpResponse::HttpResponse(const char* data) {
  char *header_break = strstr(data, "\r\n\r\n");
  int head_size = header_break - data,
      content_length = -1,
      line_number = 0;

  std::stringstream header_reader(std::string(data, head_size));
  std::string line;

  while(std::getline(header_reader, line) && line != "\r") {
    if(line_number++ == 0) {
      char *code_break = strchr(line.c_str(), ' '),
           *end;

      std::string code = line.substr(code_break - line.c_str() + 1, 3);
      m_status = std::strtol(code.c_str(), &end, 10);
      continue;
    }

    int split = line.find(':', 0);

    if(split > line.size()  - 2 || split == 0)
      continue;

    std::string key = line.substr(0, split),
                val = line.substr(split + 2);

    if(key == "Content-Length")
      content_length = std::stoi(val);

    m_headers.push_back(std::make_pair(key, val));
  }

  for(int i = 0; i < content_length; i++)
    m_body.push_back(data[head_size + 4 + i]);

  m_body.push_back('\0');
}

}

}
