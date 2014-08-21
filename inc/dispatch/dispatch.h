#ifndef _LOFTILI_DISPATCH_H
#define _LOFTILI_DISPATCH_H

#include <microhttpd.h>
#include "communication/response.h"


namespace loftili {

class Dispatch {

  public:
    Dispatch();
    ~Dispatch();
    int send(Response* res, MHD_Connection* connection);

  private:
    void headers(MHD_Response* m_res, Response* res);

};

}


#endif
