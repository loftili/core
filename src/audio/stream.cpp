#include "audio/stream.h"
#define BITS 8

namespace loftili {

AudioStream::AudioStream(std::string fname) : 
  m_handle(0), streaming(0), canceled(false),
  current_frame(0), length(0), download_res(0),
  dl_flag(false), is_finished(false), file_location(fname) {

  log = new Logger(this);
  log->info("new audio stream created");

  initialize();
}

AudioStream::~AudioStream() {
  log->info("audio stream being deleted!");

  if(m_handle) {
    log->info("audio stream closing mpg123");
    mpg123_close(m_handle);
    mpg123_delete(m_handle);
  }

  mpg123_exit();

  if(download_res)
    delete download_res;

  log->info("starting closing up threads");
  canceled = true;
  pthread_join(downloader, NULL);
  log->info("finished closing threads, deleting logger");

  delete log;
}

void* AudioStream::stream(void* stream_instance_data) {
  AudioStream* audio_stream = (AudioStream*) stream_instance_data;
  Response* res = new Response();
  Logger* log = audio_stream->log;
  Request req;

  log->info("Attempting to download file");
  audio_stream->dl_flag = true;
  req.url = audio_stream->file_location;
  req.method = "GET";
  req.send(res);
  audio_stream->dl_flag = false;

  if(res->status != 200 || res->status == NULL) {
    log->info("Problem downloading the audio file.");
    audio_stream->is_finished = true;
    delete res;
    return NULL;
  }

  audio_stream->download_res = res;

  log->info("Successfully downloaded file, sending into mpg stream");
  mpg123_feed(audio_stream->m_handle, (const unsigned char*)res->content, res->length);

  off_t frame_offset;
  unsigned char* audio;
  size_t done;

  int err = mpg123_decode_frame(audio_stream->m_handle, &frame_offset, &audio, &done);
  if(err != MPG123_NEW_FORMAT) {
    log->info("File not a valid mpg format, closing thread.");
    return NULL;
  }
  log->info("File IS a valid mpg format, continuing thread.");
  int channels, encoding;
  long rate;

  mpg123_getformat(audio_stream->m_handle, &rate, &channels, &encoding);
  audio_stream->length = res->length;

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
  } while(done > 0 && !audio_stream->canceled);

  ao_close(dev);
  audio_stream->is_finished = true;
  return NULL;
}

bool AudioStream::downloading() {
  return dl_flag;
}

off_t AudioStream::position() {
  return current_frame;
}

bool AudioStream::finished() {
  return is_finished;
}

off_t AudioStream::duration() {
  return length;
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
  if(streaming == 1) 
    return 0;

  streaming = 1;
  log->info("starting audio stream");
  pthread_create(&downloader, NULL, AudioStream::stream, (void*) this);
  return 0;
}

}
