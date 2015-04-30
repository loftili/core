#include "net/command.h"

namespace loftili {

namespace net {

Command::Command() : m_cmd(0) {
}

Command::Command(const char* data) {
  std::string cmd_str = std::string(data);
  bool is_command = cmd_str.find("CMD", 0, 3) != std::string::npos;

  if(is_command)
    m_cmd = new loftili::commands::audio::Start();
}

Command::operator bool() {
  return m_cmd != 0;
}
Command::~Command() {
}

void Command::Execute() {
  if(m_cmd) m_cmd->Execute();
}

}

}
