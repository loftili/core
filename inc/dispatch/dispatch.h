#ifndef _LOFTILI_DISPATCH_H
#define _LOFTILI_DISPATCH_H

#include <microhttpd.h>
#include "util/logger.h"
#include "dispatch/auth.h"
#include "communication/response.h"
#include "communication/request.h"

namespace loftili {

class Dispatch {

  public:
    Dispatch();
    ~Dispatch();
    int send(Response* res, MHD_Connection* connection);
    int reject(Request* req);
    bool validate(MHD_Connection* connection);

  private:
    void headers(MHD_Response* m_res, Response* res);
    Logger log;
    Auth auth;

};

}


#endif
