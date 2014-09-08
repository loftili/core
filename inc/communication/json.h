#ifndef _LOFTILI_JSON_H
#define _LOFTILI_JSON_H

#include "loftili.h"

namespace loftili {

class Json {

  public:
    Json();
    ~Json();
    bool insert(std::string key, std::string value);
    bool insert(std::string key, int value);
    char* buffer();

  private: 
    bool writing;
    JsonBuffer json_buffer;
    rapidjson::PrettyWriter<JsonBuffer> writer;

};

}

#endif
