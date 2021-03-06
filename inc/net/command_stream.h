#ifndef _LOFTILI_NET_COMMAND_STREAM_H
#define _LOFTILI_NET_COMMAND_STREAM_H

#include <stdio.h>
#include <string.h>
#include <vector>
#include "config.h"
#include "spdlog/spdlog.h"
#include "loftili.h"
#include "net/tcp_socket.h"
#include "net/generic_command.h"
#include "commands/audio/start.h"
#include "commands/audio/skip.h"

namespace loftili {

namespace net {

class CommandStream {
  public:
    CommandStream() = default;
    ~CommandStream() = default;
    CommandStream(const CommandStream&) = default;
    CommandStream& operator=(const CommandStream&) = default;

    bool operator<<(loftili::net::TcpSocket&);
    const std::shared_ptr<loftili::net::GenericCommand> Latest();
    void Pop();

  private:
    std::vector<std::shared_ptr<loftili::net::GenericCommand>> m_commands;

};

}

}

#endif
