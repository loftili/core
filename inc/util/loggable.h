#ifndef _LOFTILI_LOGGABLE_H
#define _LOFTILI_LOGGABLE_H

#include <iostream>

namespace loftili {

class Loggable { 

friend class Logger;

protected:
  virtual std::string logName() { return "Loggable"; }

};

}

#endif
