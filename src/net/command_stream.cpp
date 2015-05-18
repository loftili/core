#include "net/command_stream.h"

namespace loftili {

namespace net {

bool CommandStream::operator <<(std::unique_ptr<loftili::net::TcpSocket>& socket) {
  char *buffer = (char*) malloc(sizeof(char) * 2048);
  int received = socket->Read(buffer, 2048);

  if(received <= 0) {
    spdlog::get(LOFTILI_SPDLOG_ID)->warn("command stream\'s socket connection failed reading");
    free(buffer);
    return false;
  }

  char *cmd_break = strstr(buffer, "CMD");

  if(cmd_break == nullptr || cmd_break - buffer > 0) {
    spdlog::get(LOFTILI_SPDLOG_ID)->warn("command stream received a strange message from server");
    free(buffer);
    return false;
  }

  buffer = (char*) realloc(buffer, sizeof(char) * (received + 1));
  buffer[received] = '\0';
  m_commands.push_back(std::make_shared<loftili::net::GenericCommand>(buffer));
  free(buffer);
  return true;
}

void CommandStream::Pop() {
  m_commands.erase(m_commands.begin());
}

const std::shared_ptr<loftili::net::GenericCommand> CommandStream::Latest() {
  return m_commands.front();
}

}

}
