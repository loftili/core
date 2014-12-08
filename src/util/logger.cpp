#include "util/logger.h"

namespace loftili {

bool Logger::use_file = false;
ofstream Logger::log_stream;

Logger::Logger(string n) {
  name = n;
}

Logger::Logger(Loggable* loggable) { 
  name = loggable->logName();
}

Logger::~Logger() { 
}

void Logger::info(string msg) {
  send(msg, "INFO");
}

void Logger::info(string a, string b) {
  send(a, b, "INFO");
}


void Logger::fatal(string msg) {
  send(msg, "FATAL");
}

void Logger::send(string msg, string level) {
  string time_stamp = timestr();
  if(!use_file) {
    printf("[%s] [%s] [%s]: %s \n", name.c_str(), level.c_str(), time_stamp.c_str(), msg.c_str());
  } else {
    log_stream << "[" << name << "] [" << level << "] [" << time_stamp << "]: ";
    log_stream << msg << endl;
    log_stream.flush();
  }
}

void Logger::send(string a, string b, string level) {
  string time_stamp = timestr();
  if(!use_file) {
    printf("[%s] [%s] [%s]: %s %s \n", name.c_str(), level.c_str(), time_stamp.c_str(), a.c_str(), b.c_str());
  } else {
    log_stream << "[" << name << "] [" << level << "] [" << time_stamp << "]: ";
    log_stream << a << " " << b << endl;
    log_stream.flush();
  }
}

string Logger::timestr() {
  time(&timer);
  string time_str = ctime(&timer);
  return time_str.substr(0, time_str.length() -1);
}

LOG_STATE Logger::use(string file_name) {
  use_file = true;
  log_stream.open(file_name, ofstream::out | ofstream::app);
  return log_stream.is_open() && log_stream.good() ? LOG_STATE_READY : LOG_STATE_BAD;
}

void Logger::close() {
  log_stream.close();
}

}

