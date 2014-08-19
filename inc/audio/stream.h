#ifndef _LOFTILI_AUDIO_STREAM_H
#define _LOFTILI_AUDIO_STREAM_H

#include <pthread.h>
#include <iostream>
#include <string>
#include <mpg123.h>
#include <portaudio.h>
#include "util/logger.h"
#define FRAME_PER_BUFFER 4096

typedef PaStreamCallbackTimeInfo TimeInfo;
typedef PaStreamCallbackFlags StreamFlags;
typedef unsigned long FrameCount;

namespace loftili {

class AudioStream : public Loggable {

public:
  AudioStream(std::string fname);
  ~AudioStream();
  int start();
  int streaming;

private:
  static int playback(const void* in, void* out, FrameCount fpb, const TimeInfo* ti, StreamFlags f, void* d);

protected:
  void playback(void* output);
  std::string logName() { return "AudioStream"; }

private:
  Logger* log;
  mpg123_handle* m_handle;
  PaStream* p_stream;
  int prepare();
  bool initialize();

  std::string filename;
  int last_error;
  bool ready;
  long rate;
  int channels;
  int encoding;
  int stream_size;
  float* buffer;

};

}

#endif
