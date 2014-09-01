#include "communication/request.h"

namespace loftili {

size_t Request::receiver(char* ptr, size_t size, size_t nmemb, void* userdata) {
  size_t realsize = size * nmemb;
  return realsize;
}

Request::Request() : writer(buffer) {
  writer.StartObject();
}

Request::Request(std::string u, std::string m) : url(u), method(m), writer(buffer) {
  writer.StartObject();
}

Request::~Request() {
}

void Request::insert(std::string key, std::string value) {
  writer.String(key.c_str());
  writer.String(value.c_str(), value.length());
}

void Request::insert(std::string key, int value) {
  writer.String(key.c_str());
  writer.Int(value);
}

long Request::send() {
  writer.EndObject();
  curl = curl_easy_init();
  curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &Request::receiver);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, this);

  if(method == "POST")
    curl_easy_setopt(curl, CURLOPT_POST, 1);

  curl_easy_setopt(curl, CURLOPT_POSTFIELDS, buffer.GetString());
  struct curl_slist* header_list = NULL;
  header_list = curl_slist_append(header_list, "Content-Type: application/json");
  curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header_list);
  curl_easy_perform(curl);
  long http_code = 0;
  curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
  curl_slist_free_all(header_list);
  curl_easy_cleanup(curl);
  return http_code;
}

}
