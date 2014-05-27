#ifndef _RASBEAT_H
#define _RASBEAT_H

#define DEFAULT_PORT 8888

struct rasbeat_request {
  bool second;
  rasbeat_request() : second(false) { }
};

#endif
