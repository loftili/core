#ifndef _LOFTILI_NET_COMMAND_STREAM_H
#define _LOFTILI_NET_COMMAND_STREAM_H

#include <stdio.h>
#include <string.h>
#include <vector>
#include "config.h"
#include "spdlog/spdlog.h"
#include "net/tcp_socket.h"
#include "net/generic_command.h"
#include "commands/audio/start.h"

namespace loftili {

namespace net {

class CommandStream {
  public:
    bool operator<<(std::unique_ptr<loftili::net::TcpSocket>&);
    const std::shared_ptr<loftili::net::GenericCommand> Latest();
    void Pop();
  private:
    std::vector<std::shared_ptr<loftili::net::GenericCommand>> m_commands;
};

}

}

#endif
