#include "net/generic_command.h"

namespace loftili {

namespace net {

GenericCommand::GenericCommand() : m_cmd(0) {
}

GenericCommand::GenericCommand(const char* data) {
  std::string cmd_str = std::string(data);
  bool is_command = cmd_str.find("CMD", 0, 3) != std::string::npos;
  m_cmd = new loftili::commands::audio::Start();
}

void GenericCommand::Execute(Engine* eng) {
  if(m_cmd) m_cmd->Execute(eng);
}

void GenericCommand::operator()(Engine* eng) {
  return Execute(eng);
}

GenericCommand::operator bool() {
  return m_cmd != 0;
}
GenericCommand::~GenericCommand() {
  if(m_cmd) delete m_cmd;
}

}

}
