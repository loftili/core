#ifndef _LOFTILI_REQUEST_H
#define _LOFTILI_REQUEST_H

#include <string>
#include <iostream>
#include <sstream>
#include "loftili.h"
#include "communication/response.h"

namespace loftili {

struct Request {

  public:
    Request();
    Request(std::string url, std::string method);
    ~Request();
    void insert(std::string key, std::string value);
    void insert(std::string key, int value);
    static size_t receiver(char* ptr, size_t size, size_t nmemb, void* userdata);
    void send(Response* res);

  public:
    std::string url;
    std::string method;
    int c_method;
    JsonBuffer buffer;
    rapidjson::PrettyWriter<JsonBuffer> writer;
    CURL* curl;

  private:
    bool writing;


};

}

#endif
