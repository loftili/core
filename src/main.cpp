#include <memory>
#include <iostream>
#include "api.h"
#include "loftili.h"
#include "engine.h"

loftili::api::ApiConfiguration loftili::api::configuration = { };

int main(int argc, char* argv[]) {
  std::unique_ptr<loftili::Engine> p1 = std::unique_ptr<loftili::Engine>(new loftili::Engine(argc, argv));
  return p1->Register() && p1->Run();
}
