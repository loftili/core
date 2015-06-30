#include "audio/player.h"

namespace loftili {

namespace audio {

void Player::Stop() {
  m_state = PLAYER_STATE_STOPPED;
}

bool Player::Exists(std::string filename) {
  std::ifstream infile(filename);
  return infile.good();
}

bool Player::Play() {
  std::string url = StreamUrl();
  m_state = PLAYER_STATE_PLAYING;
  Startup();
  loftili::net::HttpClient client;
  loftili::net::HttpRequest req(loftili::net::Url(url.c_str()));
  req.Header(LOFTILI_API_TOKEN_HEADER, loftili::api::credentials.token);
  req.Header(LOFTILI_API_SERIAL_HEADER, loftili::api::configuration.serial);
  mpg123_handle* m_handle;
  m_handle = mpg123_new(NULL, NULL);

  spdlog::get(LOFTILI_SPDLOG_ID)->info("opening http request to streaming url [{0}]", url.c_str());

  if(!client.Send(req)) {
    spdlog::get(LOFTILI_SPDLOG_ID)->critical("download {0} failed completely", url.c_str());
    return false;
  }

  std::shared_ptr<loftili::net::HttpResponse> res = client.Latest();
  if(res->Status() != 200) {
    spdlog::get(LOFTILI_SPDLOG_ID)->critical("download {0} failed with status[{0}]", res->Status());
    return false;
  }

  spdlog::get(LOFTILI_SPDLOG_ID)->info("request finished with status[{0}]", res->Status());

  std::size_t last_slash = url.find_last_of("/");
  std::string filename = url.substr(last_slash + 1);
  filename += ".mp3";

  if(Exists(filename)) {
    spdlog::get(LOFTILI_SPDLOG_ID)->info("file with same name exists, removing");
    remove(filename.c_str());
  }

  if(m_state != PLAYER_STATE_PLAYING) {
    spdlog::get(LOFTILI_SPDLOG_ID)->info("playback stopped before track finished downloading, exiting");
    Shutdown();
    return false;
  }

  spdlog::get(LOFTILI_SPDLOG_ID)->info("download complete, temporarily saving to file system [{0}]", filename.c_str());
  std::ofstream download;
  download.open(filename.c_str(), std::ios::binary | std::ios::out);
  download.write(res->Body(), res->ContentLength());
  download.close();
  int err = mpg123_open(m_handle, filename.c_str());

  if(err != MPG123_OK) {
    spdlog::get(LOFTILI_SPDLOG_ID)->critical("unable to open mpg123 handle on downloaded track");
    mpg123_close(m_handle);
    mpg123_delete(m_handle);
    Shutdown();
    m_state = PLAYER_STATE_STOPPED;
    return false;
  }

  off_t frame_offset;
  unsigned char* audio;
  size_t done;
  int channels, encoding;
  long rate;

  err = mpg123_getformat(m_handle, &rate, &channels, &encoding);

  if(err != MPG123_OK) {
    spdlog::get(LOFTILI_SPDLOG_ID)->critical("invalid mpg123 format detected [{0}]", filename.c_str());
    m_state = PLAYER_STATE_STOPPED;
    mpg123_close(m_handle);
    mpg123_delete(m_handle);
    Shutdown();
    return false;
  }

  spdlog::get(LOFTILI_SPDLOG_ID)->info("mpg123 format checks out rate[{0}] channels[{1}] encoding[{2}]", rate, channels, encoding);

  ao_sample_format format;
  format.bits = mpg123_encsize(encoding) * 8;
  format.rate = rate;
  format.channels = channels;
  format.byte_format = AO_FMT_NATIVE;
  format.matrix = 0;

  int driver_id = ao_default_driver_id();
  ao_device* dev = ao_open_live(driver_id, &format, NULL);

  if(dev == NULL) {
    spdlog::get(LOFTILI_SPDLOG_ID)->critical("failed opening libao device, unable to play audio");
    mpg123_close(m_handle);
    mpg123_delete(m_handle);
    Shutdown();
    return false;
  }

  size_t buffer_size = mpg123_outblock(m_handle);
  unsigned char *buffer = (unsigned char*) malloc(buffer_size * sizeof(unsigned char));

  spdlog::get(LOFTILI_SPDLOG_ID)->info("[AUDIO PLAYBACK STARTING] opened audio driver[{0}], opening loop", driver_id); 

  while(mpg123_read(m_handle, buffer, buffer_size, &done) == MPG123_OK && m_state == PLAYER_STATE_PLAYING)
    ao_play(dev, (char*)buffer, done);

  spdlog::get(LOFTILI_SPDLOG_ID)->info("[AUDIO PLAYBACK STOPPED] audio player loop finished with state [{0}]", m_state);

  free(buffer);
  ao_close(dev);
  mpg123_close(m_handle);
  mpg123_delete(m_handle);
  Shutdown();

  remove(filename.c_str());

  return m_state == PLAYER_STATE_PLAYING;
}

Player::operator bool() {
  return m_state == PLAYER_STATE_PLAYING;
}

void Player::Startup() {
  ao_initialize();
  mpg123_init();
}

void Player::Shutdown() {
  ao_shutdown();
  mpg123_exit();
}

std::string Player::StreamUrl() {
  std::stringstream ss;
  ss << loftili::api::configuration.protocol << "://";
  ss << loftili::api::configuration.hostname << ":" << loftili::api::configuration.port << "/queues/";
  ss << loftili::api::credentials.device_id << "/stream";
  return ss.str();
}

}

}
