#ifndef _LOFTILI_H
#define _LOFTILI_H

#define LOFTILI_DEFAULT_PORT 8888

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include "config.h"
#include "headers.h"

typedef std::map<std::string, std::string> HttpHeaders;
typedef std::pair<std::string, std::string> HttpHeader;

/* forward declare libmicrohttpd classes */
class MHD_Connection;

struct ahc_info {
  void* cls;
  MHD_Connection* connection;
  const char* url;
  const char* method;
  const char* version;
  const char* data;
  size_t* data_size;
  void** con_cls;
};

#endif
