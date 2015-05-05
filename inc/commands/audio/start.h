#ifndef _LOFTILI_COMMANDS_AUDIO_START_H
#define _LOFTILI_COMMANDS_AUDIO_START_H

#include <stdio.h>
#include <string.h>
#include "net/command.h"
#include "api/registration.h"
#include "audio/playback.h"

namespace loftili {

class Engine;

namespace commands {

namespace audio {

class Start : public loftili::net::Command {
  public:
    void Execute(loftili::Engine*);
    void operator ()(loftili::Engine*);
};

}

}

}

#endif
