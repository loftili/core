#include "loftili.h"
#include "server.h"

int main(int argc, char ** argv) {
  if(argc > 1)
    std::cout << LOFTILI_PKG_VERSION << std::endl;
  else
    return loftili::Server::run();
}
