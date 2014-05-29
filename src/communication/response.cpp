#include "../../inc/communication/response.h"

namespace rasbeat {

Response::Response() {
}

Response::~Response() {
}

int Response::getLength() {
  return 12;
}

void* Response::getContent() {
  const char* page = "<h1>hi!</h1>";
  return (void*)page;
}

int Response::getStatus() {
  return 200;
}

}
