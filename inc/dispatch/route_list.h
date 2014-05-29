#ifndef _LOFTILI_ROUTE_LIST_H
#define _LOFTILI_ROUTE_LIST_H

#include <vector>
#include "controller.h"

namespace loftili {

class RouteList {

public:
  RouteList();
  ~RouteList();
  
  void add(Controller* c);
  void purge();

private:
  std::vector<Controller*> controllers;


};

}


#endif
