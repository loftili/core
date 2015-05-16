#include "audio/player.h"

namespace loftili {

namespace audio {

bool Player::Play(std::string url) {
  Startup();
  loftili::net::HttpClient client;
  loftili::net::HttpRequest req(loftili::net::Url(url.c_str()));

  mpg123_handle* m_handle;
  m_handle = mpg123_new(NULL, NULL);

  if(client.Send(req)) {
    std::shared_ptr<loftili::net::HttpResponse> res = client.Latest();
    if(res->Status() != 200) return false;
    remove("current.mp3");
    std::ofstream download;
    download.open("current.mp3", std::ios::binary | std::ios::out);
    download.write(res->Body(), res->ContentLength());
    download.close();
    int err = mpg123_open(m_handle, "current.mp3");

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

    do {
      err = mpg123_decode_frame(m_handle, &frame_offset, &audio, &done);
      switch(err) {
        case MPG123_OK:
          ao_play(dev, (char*)audio, done);
          break;
        default:
          break;
      }
    } while(done > 0);

    ao_close(dev);
  }

  mpg123_close(m_handle);
  mpg123_delete(m_handle);
  Shutdown();
  return true;
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
