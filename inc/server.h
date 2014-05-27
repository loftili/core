#ifndef _RASBEAT_SERVER_H
#define _RASBEAT_SERVER_H

#include "rasbeat.h"
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <microhttpd.h>

#define make_response(a,b,c,d) MHD_create_response_from_data(a,b,c,d)
#define queue_response(a,b,c) MHD_queue_response(a,b,c)
#define destroy_response(a) MHD_destroy_response(a)

namespace rasbeat {

class Server {

  public:
    Server();
    ~Server();

    static int run();
    static int respond(
        void* cls, 
        MHD_Connection* connection, 
        const char* url, 
        const char* method,
        const char* version,
        const char* upload_data,
        size_t* data_size,
        void** con_cls);

  private:
    static Server server;

};

}

#endif
