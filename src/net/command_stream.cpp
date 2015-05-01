#include "net/command_stream.h"

namespace loftili {

namespace net {

CommandStream& CommandStream::operator <<(const char *data) {
  m_data << data;
  return *this;
}

GenericCommand CommandStream::Transform() {
  GenericCommand cmd = m_data.str().c_str();
  m_data.str("");
  return cmd;
}

}

}
