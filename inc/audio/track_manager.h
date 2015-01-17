#ifndef _LOFTILI_TRACK_QUEUE_H
#define _LOFTILI_TRACK_QUEUE_H

#include "loftili.h"
#include "util/logger.h"
#include "communication/request.h"

namespace loftili {

enum QUEUE_STATUS {
  QUEUE_STATUS_ERRORED,
  QUEUE_STATUS_FULL,
  QUEUE_STATUS_EMPTY
};

using namespace std;

class TrackManager {

  public:
    TrackManager();
    ~TrackManager();
    QUEUE_STATUS fetch();
    Track pop();
    QUEUE_STATUS status();

  private:
    std::string endpoint();

  private:
    Logger* log;
    rapidjson::Document queue_doc;
    queue<Track> track_list;

};

}

#endif
