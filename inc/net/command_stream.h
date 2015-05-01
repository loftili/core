#ifndef _LOFTILI_NET_COMMAND_STREAM_H
#define _LOFTILI_NET_COMMAND_STREAM_H

#include "lib/stream.h"
#include "net/generic_command.h"
#include "commands/audio/start.h"

namespace loftili {

namespace net {

class CommandStream : public loftili::lib::Stream {
  public:
    CommandStream& operator<<(const char*);
    loftili::net::GenericCommand Transform();
};

}

}

#endif
