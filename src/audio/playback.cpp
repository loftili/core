#include "audio/playback.h"

namespace loftili {

namespace audio {

Playback::Playback() : 
  m_thread(0), m_state(PLAYBACK_STATE_STOPPED),
  m_player(0), m_queue(0)
  { };

Playback::~Playback() {
  if(m_thread) m_thread->join();

  if(m_player) delete m_player;
  if(m_queue) delete m_queue;
}

Playback::Playback(const Playback& other) {
}

Playback& Playback::operator=(const Playback& other) {
  return *this;
}

void Playback::Initialize(loftili::api::Registration *api_registration) {
  loftili::api::DeviceCredentials creds = api_registration->Credentials();
  m_queue = new loftili::audio::Queue(api_registration->Credentials());
  m_player = new loftili::audio::Player();
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
  while((*m_queue) >> (*m_player)) { }
  printf("queue empty - stopping\n");
  m_state = PLAYBACK_STATE_STOPPED;
}

}

}
