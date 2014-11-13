#ifndef _LOFTILI_TRACK_QUEUE_H
#define _LOFTILI_TRACK_QUEUE_H

#include "loftili.h"
#include "auth/credentials.h"
#include "util/logger.h"
#include "util/options.h"
#include "communication/request.h"

namespace loftili {

enum QUEUE_STATUS {
  QUEUE_STATUS_ERRORED,
  QUEUE_STATUS_FULL,
  QUEUE_STATUS_EMPTY
};

class TrackQueue {

  public:
    TrackQueue();
    ~TrackQueue();
    QUEUE_STATUS load();
    void initialize(Credentials creds, Options opts);

  private:
    std::string endpoint();

  private:
    Logger* log;
    rapidjson::Document queue_doc;
    Credentials device_credentials;
    Options device_options;
    std::vector<std::string> track_urls;

};

}

#endif
