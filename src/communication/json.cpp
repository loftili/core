#include "communication/json.h"

namespace loftili {

Json::Json() : writer(json_buffer), writing(false) {
}

Json::~Json() {
  if(writing)
    writer.EndObject();
}

bool Json::insert(std::string key, std::string value) {
  if(!writing)
    writer.StartObject();

  writer.String(key.c_str());
  writer.String(value.c_str(), value.length());
  writing = true;
}

bool Json::insert(std::string key, int value) {
  if(!writing)
    writer.StartObject();

  writer.String(key.c_str());
  writer.Int(value);
  writing = true;
}

char* Json::buffer() {
  if(writing)
    writer.EndObject();

  writing = false;
  return (char*)json_buffer.GetString();
}

}
