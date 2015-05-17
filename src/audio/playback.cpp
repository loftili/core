#include "audio/playback.h"

namespace loftili {

namespace audio {

void Playback::Initialize(loftili::api::Registration *api_registration) {
  loftili::api::DeviceCredentials creds = api_registration->Credentials();
  m_queue.Initialize(creds);
}

void Playback::Start() {
  if(m_state == PLAYBACK_STATE_PLAYING) return;
  m_state = PLAYBACK_STATE_PLAYING;
  m_thread = std::make_unique<std::thread>(std::bind(&Playback::Run, this));
}

void Playback::Stop() {
  m_state = PLAYBACK_STATE_STOPPED;
  m_player.Stop();
  m_thread->join();
}

void Playback::Run() {
  m_state = PLAYBACK_STATE_PLAYING;
  while(m_queue >> m_player && m_state == PLAYBACK_STATE_PLAYING) { 
  }
  m_state = PLAYBACK_STATE_STOPPED;
}

}

}
