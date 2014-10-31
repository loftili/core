#ifndef _LOFTILI_AUDIO_STREAM_H
#define _LOFTILI_AUDIO_STREAM_H

#include <pthread.h>
#include <cstring>
#include <mpg123.h>
#include <ao/ao.h>
#include "loftili.h"
#include "util/logger.h"
#include "communication/request.h"
#include "communication/response.h"
#define BITS 8


namespace loftili {

enum STREAM_STATE {
  STREAM_STATE_EMPTY,
  STREAM_STATE_PLAYING,
  STREAM_STATE_FINISHED,
  STREAM_STATE_ERRORED,
  STREAM_STATE_BUFFERING,
  STREAM_STATE_ABORTED
};

class AudioStream : public Loggable {

  public:
    AudioStream(std::string fname);
    ~AudioStream();
    off_t position();
    off_t duration();
    int start();
    STREAM_STATE state();

  protected:
    std::string logName() { return "AudioStream"; }

  private:
    static void* stream(void* stream_instance_data);

  private:
    bool initialize();

  private:
    Logger* log;
    mpg123_handle* m_handle;
    Response* download_res;
    std::string file_location;

    off_t current_frame;
    off_t length;
    STREAM_STATE current_state;

    pthread_t downloader;
};

}

#endif
