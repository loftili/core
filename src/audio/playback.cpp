#include "audio/playback.h"

namespace loftili {

namespace audio {

void Playback::Start() {
  std::unique_lock<std::mutex> mutex_lock(m_mutex);

  if(m_state == PLAYBACK_STATE_PLAYING) {
    spdlog::get(LOFTILI_SPDLOG_ID)->info("playback already started, skipping request");
    mutex_lock.unlock();
    return;
  }

  spdlog::get(LOFTILI_SPDLOG_ID)->info("playback starting, opening playback thread");
  m_state = PLAYBACK_STATE_PLAYING;
  m_stateclient.Update("playback", 1);
  m_thread = std::unique_ptr<std::thread>(new std::thread(&Playback::Run, this));
  spdlog::get(LOFTILI_SPDLOG_ID)->info("playback thread opened successfully.");
  mutex_lock.unlock();
}

void Playback::Skip() {
  spdlog::get(LOFTILI_SPDLOG_ID)->info("playback received skip request, current state [{0}]", m_state);
  if(m_state == PLAYBACK_STATE_PLAYING) Stop();
  m_queue.Pop();
  Start();
}

void Playback::Stop() {
  std::unique_lock<std::mutex> mutex_lock(m_mutex);

  if(m_state == PLAYBACK_STATE_STOPPED) {
    spdlog::get(LOFTILI_SPDLOG_ID)->info("playback alread stopped, ignoring request to stop");
    mutex_lock.unlock();
    return;
  }

  spdlog::get(LOFTILI_SPDLOG_ID)->info("stopping player and playback run thread");
  m_state = PLAYBACK_STATE_STOPPED;
  m_player.Stop();
  m_thread->join();
  mutex_lock.unlock();
}

void Playback::Run() {
  m_state = PLAYBACK_STATE_PLAYING;

  while(m_queue >> m_player && m_state == PLAYBACK_STATE_PLAYING) { 
    spdlog::get(LOFTILI_SPDLOG_ID)->info("player finished, getting next track from queue");
  }

  spdlog::get(LOFTILI_SPDLOG_ID)->info("playback run thread finishing");
  m_state = PLAYBACK_STATE_STOPPED;
  m_stateclient.Update("playback", 0);
}

}

}
