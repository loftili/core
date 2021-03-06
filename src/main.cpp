#include <memory.h>
#include <iostream>
#include "api.h"
#include "loftili.h"
#include "engine.h"

loftili::api::ApiConfiguration loftili::api::configuration = { };
loftili::api::DeviceCredentials loftili::api::credentials = { "", -1 };

int main(int argc, char* argv[]) {
  std::unique_ptr<loftili::Engine> p1 = std::unique_ptr<loftili::Engine>(new loftili::Engine());
  return p1->Initialize(argc, argv) && p1->Register() && p1->Run();
}
