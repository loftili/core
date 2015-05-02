#include "audio/playback.h"

namespace loftili {

namespace audio {

Playback::Playback() : m_thread(0), m_state(PLAYBACK_STATE_STOPPED) {
  printf("initializing audio playback engine\n");
}

Playback::~Playback() {
  if(m_thread) m_thread->join();
}

Playback::Playback(const Playback& other) {
}

Playback& Playback::operator=(const Playback& other) {
  return *this;
}

void Playback::Start() {
  if(m_state == PLAYBACK_STATE_PLAYING) return;
  printf("playback thread starting\n");
  m_state = PLAYBACK_STATE_PLAYING;
  m_thread = new std::thread((std::bind(&Playback::Run, this)));
}

void Playback::Stop() {
  printf("I am stopping!\n");
  m_state = PLAYBACK_STATE_STOPPED;
}

void Playback::Run() {
  while(m_queue >> m_player) {
  }
  printf("queue empty - stopping\n");
  m_state = PLAYBACK_STATE_STOPPED;
}

}

}
