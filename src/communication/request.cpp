#include "communication/request.h"

namespace loftili {

size_t Request::receiver(char* ptr, size_t size, size_t nmemb, void* userdata) {
  size_t realsize = size * nmemb;
  Response* res = (Response*) userdata;
  res->content = realloc(res->content, res->length + realsize + 1);
  void* end = &((char*)res->content)[res->length];
  memcpy(end, ptr, realsize);
  res->length += realsize;
  ((char*)res->content)[res->length] = 0;
  return realsize;
}

Request::Request() : writer(buffer), writing(false) {
}

Request::Request(std::string u, std::string m) : url(u), method(m), writer(buffer), writing(false) {
}

Request::~Request() {
  std::cout << "cleaning up request" << std::endl;
}

void Request::insert(std::string key, std::string value) {
  if(!writing)
    writer.StartObject();

  writer.String(key.c_str());
  writer.String(value.c_str(), value.length());
  writing = true;
}

void Request::insert(std::string key, int value) {
  if(!writing)
    writer.StartObject();

  writer.String(key.c_str());
  writer.Int(value);
  writing = true;
}

void Request::send(Response* res) {
  writer.EndObject();
  writing = false;
  curl = curl_easy_init();
  curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &Request::receiver);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*) res);

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
  res->status = (int) http_code;
}

}
