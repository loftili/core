#include "util/logger.h"

namespace loftili {

Logger::Logger(std::string n) {
  name = n;
}

Logger::Logger(Loggable* loggable) { 
  name = loggable->logName();
}

Logger::~Logger() { 
}

void Logger::info(std::string msg) {
  send(msg, "INFO");
}

void Logger::fatal(std::string msg) {
  send(msg, "FATAL");
}

void Logger::send(std::string msg, std::string level) {
  time(&timer);
  std::string time_str = ctime(&timer);
  std::string cleaned = time_str.substr(0, time_str.length() -1);
  printf("[%s] [%s] [%s]: %s \n", name.c_str(), level.c_str(), cleaned.c_str(), msg.c_str());
  //std::cout<< "[" << name << "][" << level << "][" << cleaned << "] - " << msg << std::endl;
}

}
