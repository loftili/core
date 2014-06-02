#include "util/logger.h"

namespace loftili {

Logger::Logger() { }
Logger::Logger(std::string n) { 
  name = n;
}
Logger::~Logger() { }

void Logger::info(std::string msg) {
  std::cout << msg << std::endl;
}

void Logger::fatal(std::string msg) {
  std::cout << msg << std::endl;
}

}
