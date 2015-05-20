#include "net/url.h"

namespace loftili {

namespace net {

Url::Url(const char* url_string) : m_port(-1) {
  const char *protocol_break = strstr(url_string, "://");

  if(protocol_break == nullptr) {
    protocol_break = url_string;
  } else {
    int protocol_size = protocol_break - url_string;
    m_protocol = std::string(url_string, protocol_size);
    protocol_break += 3;
  }

  const char *host_break = strstr(protocol_break, "/");
  int host_size;

  if(host_break == nullptr) {
    host_size = strlen(protocol_break);
    m_host = std::string(protocol_break, host_size);
    ParseHost();
    return;
  } else  {
    host_size = host_break - protocol_break;
  }

  m_host = std::string(protocol_break, host_size);
  ParseHost();

  const char *path_break = strchr(host_break, '\0');
  if(path_break == nullptr) return;
  int path_size = path_break - host_break;
  m_path = std::string(host_break, path_size);
}

void Url::ParseHost() {
  const char *port_break = strchr(m_host.c_str(), ':');
  if(port_break == nullptr) return;
  int host_size = port_break - m_host.c_str();
  std::string new_host = m_host.substr(0, host_size),
              port = m_host.substr(host_size + 1);
  char *end;
  int port_value = strtol(port.c_str(), &end, 10);
  m_host = new_host;
  if(port_value > 0 && port_value < 10000) m_port = port_value;
}

}

}
