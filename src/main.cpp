#include "../inc/rasbeat.h"
#include "../inc/server.h"

int main(int argc, char ** argv) {
  rasbeat::Server s;
  return s.run();
}
