#include "audio/stream.h"

namespace loftili {

int AudioStream::playback(const void* in, void* out, FrameCount fpb, const TimeInfo* ti, StreamFlags f, void* data) {
  AudioStream* stream = (AudioStream*)data;
  pthread_mutex_lock(&stream->thread_mutex);

  stream->playback(out);

  pthread_cond_broadcast(&stream->thread_cond);
  pthread_mutex_unlock(&stream->thread_mutex);
  return 0;
}

AudioStream::AudioStream(std::string fname) : 
  p_stream(0), m_handle(0), filename(fname), 
  streaming(0), rate(0), channels(0), encoding(0),
  stream_size(0), buffer(0), ready(false) {

  std::cout << "initializing mpg123 library" << std::endl;
  name = "hello world!";
  if(initialize())
    prepare();
}

AudioStream::~AudioStream() {
  mpg123_close(m_handle);
  mpg123_delete(m_handle);
}

void AudioStream::clean() {
  mpg123_close(m_handle);
  mpg123_delete(m_handle);

  std::cout << "Audiostream cleanup" << std::endl;
  std::cout << " - portaudio cleanup" << std::endl;
}

bool AudioStream::initialize() {
  bool ok = true;
  m_handle = mpg123_new(NULL, NULL);
  int m_error = mpg123_open(m_handle, filename.c_str());
  if(m_error == MPG123_ERR) {
    std::cout << "error opening file" << std::endl;
    ok = false;
  }
  return ok;
}

int AudioStream::prepare() {
  int m_error;
  std::cout << "successfully opened file" << std::endl;
  mpg123_param(m_handle, MPG123_ADD_FLAGS, MPG123_FORCE_FLOAT, 0.);

  m_error = mpg123_getformat(m_handle, &rate, &channels, &encoding);
  if(m_error != MPG123_OK) {
    std::cout << "bad file format!" << std::endl;
    clean();
    return 1;
  }

  std::cout << "file format checked out, prepping buffer" << std::endl;

  mpg123_format_none(m_handle);
  mpg123_format(m_handle, rate, channels, encoding);

  stream_size = FRAME_PER_BUFFER * 2.0;
  buffer = (float*) malloc(sizeof(float) * stream_size);

  ready = true;
}

int AudioStream::start() {
  if(!ready || streaming == 1) 
    return 0;

  int m_error = Pa_OpenDefaultStream(&p_stream, 0, 2, paFloat32, 44100, FRAME_PER_BUFFER, &AudioStream::playback, (void*)this);
  if(m_error != paNoError) {
    std::cout << "unable to open portaudio stream!" << std::endl;
    return 1;
  }

  streaming = 1;
  std::cout << "portaudio stream opened, opening threads" << std::endl;
  m_error = Pa_StartStream(p_stream);
  return 0;
}

void AudioStream::playback(void* output_buffer) {
  size_t done = 0;
  mpg123_read(m_handle, (unsigned char*)buffer, stream_size * sizeof(float), &done);
  memcpy(output_buffer, buffer, sizeof(float) * stream_size);
}

bool AudioStream::isPlaying() {
  std::cout << "streaming: " << streaming << std::endl;
  return streaming;
}

int AudioStream::stop() {
  if(!ready || streaming == 0) 
    return 0;

  if(buffer != 0) {
    free(buffer);
    buffer = 0;
  }

  Pa_StopStream(p_stream);
  Pa_CloseStream(p_stream);

  streaming = 0;
  return 0;
}

}
