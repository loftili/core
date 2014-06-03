#ifndef _LOFTILI_PLAYER_H
#define _LOFTILI_PLAYER_H

#define NUM_SECONDS 5
#define TABLE_SIZE 200
#define SAMPLE_RATE 44100
#define FRAMES_PER_BUFFER 64
#ifndef M_PI
#define M_PI 3.14159265
#endif

#include <math.h>
#include <portaudio.h>
#include "util/logger.h"

namespace loftili {

class AudioPlayer : public Loggable {

public:
  AudioPlayer();
  ~AudioPlayer();
  void start();
  void stop();
  bool isPlaying();

protected:
  std::string logName() { return "AudioPlayer"; }

// static
private:
  static int onPlay(const void* input, void* output, unsigned long fpb, const PaStreamCallbackTimeInfo* time_info, PaStreamCallbackFlags flags, void* data);
  static void onFinish(void* data);

// instance
private:
  int whilePlaying(const void* input, void* output, unsigned long fpb, const PaStreamCallbackTimeInfo* time_info, PaStreamCallbackFlags flags);
  int onFinished();
  bool prepare();

private:
  Logger* log;
  bool playing;
  bool ready;
  PaStream* stream;
  PaStreamParameters output_config;
  PaError last_error;
  const PaDeviceInfo* device_info;
  float sine[TABLE_SIZE];
  int left_phase;
  int right_phase;
  char message[20];


};

}


#endif
