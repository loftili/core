#ifndef _RASBEAT_SERVER_H
#define _RASBEAT_SERVER_H

#include <microhttpd.h>
#include "rasbeat.h"
#include "router.h"
#include "communication/request.h"

namespace rasbeat {

class Server {

  public:
    Server();
    ~Server();
    int process(struct ahc_info info);

  private:
    int queueResponse(Response r, MHD_Connection* connection);
    Router router;

  public:
    static int run();
    static int ahc(
      void* cls, 
      MHD_Connection* connection, 
      const char* url, 
      const char* method,
      const char* version,
      const char* upload_data,
      size_t* data_size,
      void** con_cls
    );

  private:
    static Server* server_instance;

};

}

#endif
