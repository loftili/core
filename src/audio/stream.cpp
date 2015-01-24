#include "audio/stream.h"
#define BITS 8

namespace loftili {

size_t AudioStream::download(void* contents, size_t size, size_t nmemb, void* data) {
  AudioStream* stream = (AudioStream*) data;
  size_t realsize = size * nmemb;

  stream->download_buffer = (unsigned char*) realloc(stream->download_buffer, stream->download_size + realsize + 1);
  void* end = &((char*)stream->download_buffer)[stream->download_size];
  memcpy(end, contents, realsize);
  stream->download_size += realsize;
  ((unsigned char*)stream->download_buffer)[stream->download_size] = 0;

  return realsize;
}

AudioStream::AudioStream(std::string fname) {
  log = new Logger(this);
  log->info("new audio stream created");
  m_handle = 0;
  current_frame = 0;
  length = 0;
  file_location = fname;
  current_state = STREAM_STATE_EMPTY;
  download_buffer = 0;
  download_size = 0;

  initialize();
}

AudioStream::~AudioStream() {
  log->info("audio stream being deleted!");

  current_state = STREAM_STATE_ABORTED;

  log->info("starting closing up threads");
  pthread_join(downloader, NULL);
  log->info("finished closing threads, deleting logger");

  if(m_handle) {
    log->info("audio stream closing mpg123");
    mpg123_close(m_handle);
    mpg123_delete(m_handle);
  }

  mpg123_exit();

  delete log;
}

void* AudioStream::stream(void* stream_instance_data) {
  AudioStream* audio_stream = (AudioStream*) stream_instance_data;
  Logger* log = audio_stream->log;

  log->info("attempting to download file");

  CURL* curl = curl_easy_init();
  CURLcode res;
  curl_easy_setopt(curl, CURLOPT_URL, audio_stream->file_location.c_str());
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, AudioStream::download);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, audio_stream);
  res = curl_easy_perform(curl);
  curl_easy_cleanup(curl);

  if(res != CURLE_OK) {
    log->info("Problem downloading the audio file.");
    audio_stream->current_state = STREAM_STATE_ERRORED;
    return NULL;
  }

  if(audio_stream->current_state == STREAM_STATE_ABORTED) {
    return NULL;
  }

  log->info("Successfully downloaded file, sending into mpg stream");
  mpg123_feed(audio_stream->m_handle, audio_stream->download_buffer, audio_stream->download_size);

  off_t frame_offset;
  unsigned char* audio;
  size_t done;
  int channels, encoding;
  long rate;

  // int err = mpg123_decode_frame(audio_stream->m_handle, &frame_offset, &audio, &done);
  int err = mpg123_getformat(audio_stream->m_handle, &rate, &channels, &encoding);

  if(err != MPG123_OK) {
    audio_stream->current_state = STREAM_STATE_ERRORED;
    log->info("file does not appear to be valid mpg format, closing thread.");
    std::stringstream ss;
    ss << "error: " << err;
    log->info(ss.str());
    return NULL;
  }

  audio_stream->current_state = STREAM_STATE_PLAYING;

  log->info("File is a valid mpg format, continuing thread.");

  mpg123_getformat(audio_stream->m_handle, &rate, &channels, &encoding);
  audio_stream->length = audio_stream->download_size;

  ao_sample_format format;
  format.bits = mpg123_encsize(encoding) * BITS;
  format.rate = rate;
  format.channels = channels;
  format.byte_format = AO_FMT_NATIVE;
  format.matrix = 0;

  ao_device* dev = ao_open_live(ao_default_driver_id(), &format, NULL);

  do {
    err = mpg123_decode_frame(audio_stream->m_handle, &frame_offset, &audio, &done);
    switch(err) {
      case MPG123_OK:
        ao_play(dev, (char*)audio, done);
        audio_stream->current_frame = mpg123_tell_stream(audio_stream->m_handle);
        break;
      default:
        break;
    }
  } while(done > 0 && audio_stream->current_state != STREAM_STATE_ABORTED);

  audio_stream->current_state = STREAM_STATE_FINISHED;

  ao_close(dev);
  return NULL;
}

off_t AudioStream::position() {
  return current_frame;
}

off_t AudioStream::duration() {
  return length;
}

STREAM_STATE AudioStream::state() {
  return current_state;
}

bool AudioStream::initialize() {
  bool ok = true;
  log->info("initializing audio stream - opening mpg handle");

  mpg123_init();

  m_handle = mpg123_new(NULL, NULL);
  int m_error = mpg123_open_feed(m_handle);
  if(m_error == MPG123_ERR) {
    log->fatal("failed opening the audio stream\'s file");
    ok = false;
  }
  log->info("successfully opened file, proceeding to portaudio init");

  return ok;
}

int AudioStream::start() {
  if(current_state != STREAM_STATE_EMPTY)
    return 0;

  current_state = STREAM_STATE_BUFFERING;
  log->info("starting audio stream");
  pthread_create(&downloader, NULL, AudioStream::stream, (void*) this);
  return 0;
}

}
