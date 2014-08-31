#include "util/registration.h"

namespace loftili {

Registration::Registration(Options opts) : log("registration") {
  options = opts;
}

size_t Registration::receiver(char* ptr, size_t size, size_t nmemb, void* userdata) {
  size_t realsize = size * nmemb;
  Registration* r = (Registration*) userdata;
  return realsize;
}

bool Registration::attempt() {
  log.info("attempting to register...");
  JsonBuffer buffer;
  rapidjson::PrettyWriter<JsonBuffer> writer(buffer);

  writer.StartObject();
  writer.String("username");
  writer.String(options.username.c_str(), options.username.length());

  writer.String("password");
  writer.String(options.password.c_str(), options.password.length());

  writer.String("devicename");
  writer.String(options.devicename.c_str(), options.devicename.length());

  writer.String("port");
  writer.Int(options.port);
  writer.EndObject();

  std::string api_host = options.api_host != "" ? options.api_host : LOFTILI_API_HOME;
  std::string registration_endpoint = "/registration";
  log.info(api_host + registration_endpoint);

  CURL* curl;
  curl = curl_easy_init();
  curl_easy_setopt(curl, CURLOPT_URL, (api_host + registration_endpoint).c_str());
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &Registration::receiver);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, this);
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
  log.info("server returned:");
  log.info(std::to_string(http_code));
  return (http_code > 300) ? false : true;
}

}
