#ifndef _LOFTILI_COMMANDS_AUDIO_START_H
#define _LOFTILI_COMMANDS_AUDIO_START_H

#include <stdio.h>
#include <string.h>
#include "lib/command.h"

namespace loftili {

namespace commands {

namespace audio {

class Start : public loftili::lib::Command {
  public:
    void Execute();
};

}

}

}

#endif
