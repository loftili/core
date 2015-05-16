#include "net/url.h"

namespace loftili {

namespace net {

Url::Url(const char* url_string) {
  char *protocol_break = strstr(url_string, "://");
  if(protocol_break == nullptr) return;
  int protocol_size = protocol_break - url_string;
  m_protocol = std::string(url_string, protocol_size);
  char *host_break = strstr(protocol_break + 3, "/");
  int host_size = host_break - (protocol_break + 3);
  if(host_break == nullptr) return;
  m_host = std::string(protocol_break + 3, host_size);

  char *port_break, *end;
  if((port_break = strchr(m_host.c_str(), ':')) != nullptr) {
    m_port = std::strtol(m_host.substr((port_break + 1) - m_host.c_str(), std::string::npos).c_str(), &end, 10);
    m_host = m_host.substr(0, port_break - m_host.c_str());
  } else
    m_port = 80;

  char *path_break = strchr(host_break, '\0');
  if(path_break == nullptr) return;
  int path_size = path_break - host_break;
  m_path = std::string(host_break, path_size);
}

}

}
