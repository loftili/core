#include "net/url.h"


namespace loftili {

namespace net {

Url::Url() : m_path(""), m_host(""), m_port(-1), m_protocol("") { };

Url::Url(const char *url_str) : m_port(-1) {
  int i = 0;
  const std::string prot_end("://");
  std::string url_s(url_str);

  std::string::iterator place = std::search(url_s.begin(), url_s.end(), prot_end.begin(), prot_end.end());
  int protocol_length = std::distance(url_s.begin(), place);

  if(place == url_s.end())
    return;

  for(; i < protocol_length; i++)
    m_protocol += tolower(url_s[i]);

  std::advance(place, prot_end.length());

  std::string::iterator host_end = std::find(place, url_s.end(), '/');
  int host_length = std::distance(place, host_end);

  for(i = 0; i < host_length; i++)
    m_host += tolower(url_s[i + protocol_length + 3]);

  std::string::iterator port_start = std::find(m_host.begin(), m_host.end(), ':');

  if(host_length > 0 && port_start != m_host.end()) {
    int hostname_dist = std::distance(m_host.begin(), port_start);
    std::string hostname = m_host.substr(0, hostname_dist);
    std::string port_num = m_host.substr(hostname_dist + 1, std::string::npos);
    m_host = hostname;
    m_port = std::stoi(port_num);
  }

  std::advance(place, host_length);

  std::string::iterator path_end = std::find(place, url_s.end(), '?');
  int path_length = std::distance(place, path_end);

  for(i = 0; i < path_length; i++)
    m_path += tolower(url_s[i + host_length + protocol_length + 3]);


};

std::string Url::Path() const { return m_path; }
std::string Url::Protocol() const { return m_protocol; }
std::string Url::Host() const { return m_host; }
int Url::Port() const { return m_port; }

}

}
