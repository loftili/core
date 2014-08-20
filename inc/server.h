#ifndef _LOFTILI_SERVER_H
#define _LOFTILI_SERVER_H

#include <microhttpd.h>
#include "loftili.h"
#include "util/options.h"
#include "dispatch/router.h"
#include "communication/request.h"
#include "communication/response.h"

namespace loftili {

class Server {

  public:
    Server();
    ~Server();
    int process(struct ahc_info info);

  private:
    int queueResponse(Response* r, MHD_Connection* c);
    Router router;

  public:
    static int run(Options opts);
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
