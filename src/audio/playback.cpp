#include "audio/playback.h"

namespace loftili {

namespace audio {

Playback::Playback() {
  printf("initializing audio playback engine\n");
}

Playback::~Playback() {
}

Playback::Playback(const Playback& other) {
}

Playback& Playback::operator=(const Playback& other) {
  return *this;
}

void Playback::Start() {
  printf("I am starting!\n");
}

void Playback::Stop() {
  printf("I am stopping!\n");
}

}

}
