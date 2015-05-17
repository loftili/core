#include "net/generic_command.h"

namespace loftili {

namespace net {

GenericCommand::GenericCommand() : m_cmd(0) {
}

GenericCommand::GenericCommand(const char* data) {
  std::string cmd_str = std::string(data);
  bool is_command = cmd_str.find("CMD", 0, 3) != std::string::npos;

  if(!is_command)
    return;

  std::string cmd = cmd_str.substr(4);
  const char *type_break = strchr(cmd.c_str(), ':');
  int type_length = type_break - cmd.c_str();

  if(cmd.substr(0, type_length) == "audio") {
    if(cmd.substr(type_length + 1) == "stop") m_cmd = new loftili::commands::audio::Stop();
    else m_cmd = new loftili::commands::audio::Start();
    return;
  }

  return;
}

void GenericCommand::Execute(Engine* eng) {
  if(!m_cmd) return;

  m_cmd->Execute(eng);
  delete m_cmd;
  m_cmd = 0;
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
