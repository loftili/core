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
  m_thread = std::unique_ptr<std::thread>(new std::thread(std::bind(&Playback::Run, this)));
}

void Playback::Stop() {
  printf("I am stopping!\n");
  m_state = PLAYBACK_STATE_STOPPED;
}

void Playback::Run() {
  while(m_queue >> m_player) { 
  }
  m_state = PLAYBACK_STATE_STOPPED;
}

}

}
