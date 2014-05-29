#include "../inc/server.h"

namespace rasbeat {

Server Server::server_instance = Server();

Server::Server() : router() {
  auto a = [] () { };
}

Server::~Server() {
}

int Server::run() {

  MHD_Daemon* daemon = MHD_start_daemon(MHD_USE_DEBUG | MHD_USE_SELECT_INTERNALLY, 8888, NULL, NULL, &ahc, NULL, MHD_OPTION_END);

  if(daemon != NULL)
    std::cout << "Daemon started successfully!" << std::endl;

  std::string exit_code = "";
  while(exit_code != "exit") {
    std::cin >> exit_code;
  }

  MHD_stop_daemon(daemon);
  return 0;
}

int Server::ahc(
    void* cls, 
    MHD_Connection* connection, 
    const char* url, 
    const char* method,
    const char* version,
    const char* upload_data,
    size_t* data_size,
    void** con_cls) {

  int ret;
  Request* request = static_cast<Request*>(*con_cls);

  if(request == NULL) {
    request = new Request(url, method);
    std::cout << "con_cls is nothing:: [" << request->url << "] " << url << std::endl;
    *con_cls = request;
    return MHD_YES;
  } else {
    std::cout << "con_cls is something: [" << request->url << "] " << std::endl;
  }
  
  return MHD_NO;
}

}
