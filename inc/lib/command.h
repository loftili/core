#ifndef _LOFTILI_LIB_COMMAND_H
#define _LOFTILI_LIB_COMMAND_H

namespace loftili {

namespace lib {

class Command {
  public:
    virtual void Execute() = 0;
};

}

}

#endif
