#ifndef _LOFTILI_NET_RESPONSE_STREAM_H
#define _LOFTILI_NET_RESPONSE_STREAM_H

#include <vector>
#include "lib/stream.h"
#include "net/response.h"

namespace loftili {

namespace net {

class ResponseStream : public loftili::lib::Stream {
  public:
    ResponseStream() : m_content_length(-1), m_has_headers(false), m_ok(true) { };
    ~ResponseStream() = default;
    ResponseStream(const ResponseStream&) = default;
    ResponseStream& operator=(const ResponseStream&) = default;
    ResponseStream& operator <<(const char*);
    int Count() const { return m_responses.size(); };
    bool Ok() { return m_ok; }
    bool operator >>(Response&);

  private:
    void Reset();

    bool m_ok;
    bool m_has_headers;
    int m_content_length;
    std::vector<Response> m_responses;
};

}

}


#endif
