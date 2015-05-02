#ifndef _LOFTILI_NET_RESPONSE_STREAM_H
#define _LOFTILI_NET_RESPONSE_STREAM_H

#include "lib/stream.h"

namespace loftili {

namespace net {

class ResponseStream : public loftili::lib::Stream {
  public:
    ResponseStream& operator <<(const char*);
    bool Finished();
  private:
    bool m_has_headers;
    int m_content_length = -1;
};

}

}


#endif
