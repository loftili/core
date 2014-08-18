#ifndef _LOFTILI_PLAYER_H
#define _LOFTILI_PLAYER_H

#define NUM_SECONDS 5
#define TABLE_SIZE 200
#define SAMPLE_RATE 44100
#define FRAMES_PER_BUFFER 64
#ifndef M_PI
#define M_PI 3.14159265
#endif

#include <string>
#include <iostream>
#include <sstream>

#include <math.h>
#include <portaudio.h>
#include <mpg123.h>
#include "util/logger.h"

typedef PaStreamCallbackTimeInfo TimeInfo;
typedef PaStreamCallbackFlags StreamFlags;
typedef unsigned long FrameCount;

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
  static int onPlay(const void* input, void* output, FrameCount fpb, const TimeInfo* time_info, StreamFlags flags, void* data);
  static void onFinish(void* data);

// instance
private:
  int whilePlaying(const void* input, void* output, FrameCount fpb, const TimeInfo* time_info, StreamFlags flags);
  int onFinished();
  bool prepare();
  bool readFile();

private:
  Logger* log;
  bool playing;
  bool ready;

  PaStream* stream;
  PaStreamParameters output_config;
  PaError last_error;
  const PaDeviceInfo* device_info;

  mpg123_handle* file_handle;

  float sine[TABLE_SIZE];
  int left_phase;
  int right_phase;
  char message[20];

};

}

#endif
