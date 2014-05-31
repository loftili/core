#include "audio/player.h"

namespace loftili {

Player::Player() : freq(440.0) {
  std::cout << "creating the player" << std::endl;
  ao_initialize();
  ao_driver = ao_default_driver_id();

  memset(&format, 0, sizeof(format));
  format.bits = 16;
  format.bits = 16;
  format.channels = 2;
  format.rate = 44100;
  format.byte_format = AO_FMT_LITTLE;

  device = ao_open_live(ao_driver, &format, NULL);
  if(device == NULL)
    std::cout << "NO DEVICE!" << std::endl;
  else
    std::cout << "DEVICE CREATED" << std::endl;
}

Player::~Player() {
  std::cout << "closing the player" << std::endl;
  ao_close(device);
  ao_shutdown();
}

void Player::start() {
  std::cout << "starting the player" << std::endl;
  int i;

  buf_size = format.bits/8 * format.channels * format.rate;
  buffer = (char*)calloc(buf_size, sizeof(char));

  for (i = 0; i < format.rate; i++) {
    sample = (int)(0.75 * 32768.0 * sin(2 * M_PI * freq * ((float) i/format.rate)));

    buffer[4*i] = buffer[4*i+2] = sample & 0xff;
    buffer[4*i+1] = buffer[4*i+3] = (sample >> 8) & 0xff;
  }

  ao_play(device, buffer, buf_size);

}

void Player::stop() {
  std::cout << "stopping the player" << std::endl;
}

}
