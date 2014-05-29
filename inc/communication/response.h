#ifndef _RASBEAT_RESPONSE_H
#define _RASBEAT_RESPONSE_H

namespace rasbeat {

class Response {

  public:
    Response();
    ~Response();

    int getLength();
    void* getContent();
    int getStatus();

};

}

#endif
