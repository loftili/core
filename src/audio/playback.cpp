#include "audio/playback.h"

namespace loftili {

namespace audio {

void Playback::Initialize(loftili::api::Registration *api_registration) {
  loftili::api::DeviceCredentials creds = api_registration->Credentials();
  m_queue.Initialize(creds);
}

void Playback::Start() {
  if(m_state == PLAYBACK_STATE_PLAYING) return;
  spdlog::get(LOFTILI_SPDLOG_ID)->info("playback starting, opening playback thread");
  m_state = PLAYBACK_STATE_PLAYING;
  m_thread = std::unique_ptr<std::thread>(new std::thread(std::bind(&Playback::Run, this)));
}

void Playback::Stop() {
  spdlog::get(LOFTILI_SPDLOG_ID)->info("stopping player and playback run thread");
  m_state = PLAYBACK_STATE_STOPPED;
  m_player.Stop();
  m_thread->join();
}

void Playback::Run() {
  m_state = PLAYBACK_STATE_PLAYING;
  while(m_queue >> m_player && m_state == PLAYBACK_STATE_PLAYING) { 
    spdlog::get(LOFTILI_SPDLOG_ID)->info("player finished, getting next track from queue");
  }
  spdlog::get(LOFTILI_SPDLOG_ID)->info("playback run thread finishing");
  m_state = PLAYBACK_STATE_STOPPED;
}

}

}
