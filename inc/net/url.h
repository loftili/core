#ifndef _LOFTILI_NET_URL_H
#define _LOFTILI_NET_URL_H

#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <functional>

namespace loftili {

namespace net {

class Url {
  public:
    Url();
    Url(const char *);
    Url(const Url&) = default;
    Url& operator=(const Url&) = default;

    ~Url() = default;

    std::string Path() const;
    std::string Host() const;
    std::string Protocol() const;
    int Port() const;
  private:
    std::string m_protocol;
    std::string m_path;
    std::string m_host;
    int m_port;
};

}

}

#endif
