#include "loftili.h"

#include "engine.h"

int main(int argc, char* argv[]) {
  std::unique_ptr<loftili::Engine> p1(new loftili::Engine);
  return p1->Run();
}
