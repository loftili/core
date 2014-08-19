#ifndef _LOFTILI_AUDIO_STREAM_H
#define _LOFTILI_AUDIO_STREAM_H

#include <pthread.h>
#include <iostream>
#include <string>
#include <mpg123.h>
#include <portaudio.h>
#define FRAME_PER_BUFFER 4096

typedef PaStreamCallbackTimeInfo TimeInfo;
typedef PaStreamCallbackFlags StreamFlags;
typedef unsigned long FrameCount;

namespace loftili {

class AudioStream {

  public:
    AudioStream(std::string fname);
    ~AudioStream();
    int start();
    int stop();
    void clean();
    int streaming;

  private:
    static int playback(const void* in, void* out, FrameCount fpb, const TimeInfo* ti, StreamFlags f, void* d);

  protected:
    void playback(void* output);
    bool isPlaying();

  private:
    mpg123_handle* m_handle;
    PaStream* p_stream;
    int prepare();
    bool initialize();
    std::string name;

    std::string filename;
    int last_error;
    bool ready;
    long rate;
    int channels;
    int encoding;
    int stream_size;
    pthread_t load_thread;
    pthread_mutex_t thread_mutex;
    pthread_cond_t thread_cond;
    float* buffer;

};

}

#endif
