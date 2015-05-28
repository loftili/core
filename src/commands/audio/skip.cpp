#include "commands/audio/skip.h"
#include "engine.h"

namespace loftili {

namespace commands {

namespace audio {

void Skip::Execute(loftili::Engine *engine) {
  loftili::audio::Playback *playback = engine->Get<loftili::audio::Playback>();
  if(!playback) return;
  playback->Skip();
}

void Skip::operator()(loftili::Engine *engine) {
  return Execute(engine);
}

}

}

}
