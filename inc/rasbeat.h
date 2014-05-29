#ifndef _RASBEAT_H
#define _RASBEAT_H

#define RASB_DEFAULT_PORT 8888
#define RASB_EMPTY_RESPONSE "<html><head></head><body></body></html>"

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
