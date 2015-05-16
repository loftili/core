#include "net/command_stream.h"

namespace loftili {

namespace net {

bool CommandStream::operator <<(std::unique_ptr<loftili::net::TcpSocket>& socket) {
  char buffer[2048];
  int received = socket->Read(buffer, 2048);
  if(received <= 0) return false;
  char *cmd_break = strstr(buffer, "CMD");
  if(cmd_break == nullptr || cmd_break - buffer > 0) return false;
  m_commands.push_back(std::make_shared<loftili::net::GenericCommand>(buffer));
  return true;
}

const std::shared_ptr<loftili::net::GenericCommand> CommandStream::Latest() {
  return m_commands.front();
}

}

}
