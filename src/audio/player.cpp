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

bool Player::Play(std::string url) {
  Startup();
  loftili::net::HttpClient client;
  loftili::net::HttpRequest req(loftili::net::Url(url.c_str()));

  mpg123_handle* m_handle;
  m_handle = mpg123_new(NULL, NULL);

  spdlog::get(LOFTILI_SPDLOG_ID)->info("attempting to download track...");

  if(!client.Send(req) || client.Latest()->Status() != 200) {
    spdlog::get(LOFTILI_SPDLOG_ID)->critical("download {0} failed", url.c_str());
    return false;
  }

  std::shared_ptr<loftili::net::HttpResponse> res = client.Latest();
  std::size_t last_slash = url.find_last_of("/");
  std::string filename = url.substr(last_slash + 1);
  filename += ".mp3";

  if(Exists(filename)) {
    spdlog::get(LOFTILI_SPDLOG_ID)->info("file with same name exists, removing");
    remove(filename.c_str());
  }

  spdlog::get(LOFTILI_SPDLOG_ID)->info("download complete, temporarily saving to file system [{0}]", filename.c_str());
  std::ofstream download;
  download.open(filename.c_str(), std::ios::binary | std::ios::out);
  download.write(res->Body(), res->ContentLength());
  download.close();
  int err = mpg123_open(m_handle, filename.c_str());

  if(err != MPG123_OK) {
    mpg123_close(m_handle);
    mpg123_delete(m_handle);
    Shutdown();
    return false;
  }

  off_t frame_offset;
  unsigned char* audio;
  size_t done;
  int channels, encoding;
  long rate;

  err = mpg123_getformat(m_handle, &rate, &channels, &encoding);
  if(err != MPG123_OK) {
    mpg123_close(m_handle);
    mpg123_delete(m_handle);
    Shutdown();
  }

  ao_sample_format format;
  format.bits = mpg123_encsize(encoding) * 8;
  format.rate = rate;
  format.channels = channels;
  format.byte_format = AO_FMT_NATIVE;
  format.matrix = 0;

  ao_device* dev = ao_open_live(ao_default_driver_id(), &format, NULL);
  if(dev == NULL) {
    spdlog::get(LOFTILI_SPDLOG_ID)->critical("failed opening libao device, unable to play audio");
    mpg123_close(m_handle);
    mpg123_delete(m_handle);
    Shutdown();
    return false;
  }

  m_state = PLAYER_STATE_PLAYING;
  size_t buffer_size = mpg123_outblock(m_handle);
  unsigned char *buffer = (unsigned char*) malloc(buffer_size * sizeof(unsigned char));

  while(mpg123_read(m_handle, buffer, buffer_size, &done) == MPG123_OK && m_state == PLAYER_STATE_PLAYING)
    ao_play(dev, (char*)buffer, done);

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

}

}
