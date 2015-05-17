#include "commands/audio/stop.h"
#include "engine.h"

namespace loftili {

namespace commands {

namespace audio {

void Stop::Execute(loftili::Engine *engine) {
  loftili::audio::Playback *playback = engine->Get<loftili::audio::Playback>();
  if(!playback) return;
  playback->Stop();
}

void Stop::operator()(loftili::Engine *engine) {
  return Execute(engine);
}

}

}

}
