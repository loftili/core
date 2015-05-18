#ifndef _LFTNET_URL_H
#define _LFTNET_URL_H

#include <stdio.h>
#include <string.h>
#include <iostream>

namespace loftili {
namespace net {
class Url {
  public:
    Url(const char *);
    Url() = default;
    Url(const Url&) = default;
    Url& operator=(const Url&) = default;
    ~Url() = default;

    std::string Path() const { return m_path; }
    int Port() const { return m_port; }
    std::string Host() const { return m_host; }
    std::string Protocol() const { return m_protocol; }
  private:
    std::string m_host;
    std::string m_path;
    int m_port;
    std::string m_protocol;
};

}
}

#endif
