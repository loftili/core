#ifndef _LOFTILI_H
#define _LOFTILI_H

#define LOFTILI_DEFAULT_PORT 8888
#define LOFTILI_EMPTY_RESPONSE "<html><head></head><body></body></html>"
#define LOFTILI_EMPTY_RESPONSE_LEN strlen(LOFTILI_EMPTY_RESPONSE)

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

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
