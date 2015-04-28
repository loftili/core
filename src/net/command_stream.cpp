#include "net/command_stream.h"

namespace loftili {

namespace net {

CommandStream& CommandStream::operator <<(const char *data) {
  printf("-----\n");
  printf("%s", data);
  printf("\n-----\n");
  return *this;
}

Command* CommandStream::LastCommand() {
  return 0;
}

}

}
