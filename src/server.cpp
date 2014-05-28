#include "../inc/server.h"

namespace rasbeat {

Server::Server() {
}

Server::~Server() {
}

int Server::run() {
  std::cout << "WHOA!" << std::endl;
  MHD_Daemon* daemon = MHD_start_daemon(MHD_USE_DEBUG | MHD_USE_SELECT_INTERNALLY, 8888, NULL, NULL, &respond, NULL, MHD_OPTION_END);

  if(daemon != NULL)
    std::cout << "Daemon started successfully!" << std::endl;

  std::string exit_code = "";
  while(exit_code != "exit") {
    std::cin >> exit_code;
  }

  MHD_stop_daemon(daemon);
  return 0;
}

int Server::respond(
    void* cls, 
    MHD_Connection* connection, 
    const char* url, 
    const char* method,
    const char* version,
    const char* upload_data,
    size_t* data_size,
    void** con_cls) {

  int ret;
  static int dummy;
  const char* page = "<h1>HI!</h1>";
  MHD_Response* response;
  Request* request;

  if(&dummy != *con_cls) {
    std::cout << "con_cls is nothing: " << url << std::endl;
    *con_cls = &dummy;
    return MHD_YES;
  } else {
    std::cout << "con_cls is something: " << url << std::endl;
  }
  
  response = make_response(strlen(page), (void*)page, MHD_NO, MHD_NO);
  ret = queue_response(connection, MHD_HTTP_OK, response);
  destroy_response(response);
  return ret;
}

}
