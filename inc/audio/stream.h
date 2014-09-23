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

class AudioStream : public Loggable {

  public:
    AudioStream(std::string fname);
    ~AudioStream();
    off_t position();
    off_t duration();
    bool downloading();
    bool finished();
    int start();

  public:
    int streaming;

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
    bool canceled;
    bool dl_flag;
    bool is_finished;

    pthread_t downloader;
};

}

#endif
