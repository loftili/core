#include "../inc/server.h"

namespace rasbeat {

Server* Server::server_instance;

Server::Server() : router() {

}

int Server::process(struct ahc_info info) {
  Request* request = static_cast<Request*>(*info.con_cls);

  // first attempts are meant to handle the headers
  // only. the data comes in second
  if(request == NULL) {
    request = new Request();
    *info.con_cls = request;
    return MHD_YES;
  }

  Response r = router.handle(request);
  free(request);
  return queueResponse(r, info.connection);
}

int Server::queueResponse(Response r, MHD_Connection* connection) {
  int length = r.getLength();
  void* data = r.getContent();
  int status = r.getStatus();

  struct MHD_Response* response;

  response = MHD_create_response_from_data(length, data, MHD_NO, MHD_NO);
  int ret = MHD_queue_response(connection, status, response);
  MHD_destroy_response(response);
  return ret;
}

Server::~Server() {
}

int Server::run() {
  server_instance = new Server();

  MHD_Daemon* daemon = MHD_start_daemon(
    MHD_USE_DEBUG | MHD_USE_SELECT_INTERNALLY, 
    RASB_DEFAULT_PORT, NULL, 
    NULL, &ahc, NULL, 
    MHD_OPTION_END);

  if(daemon == NULL) {
    std::cout << "Daemon unable to start successfully!" << std::endl;
    return 1;
  }

  std::string exit_code = "";
  while(exit_code != "exit") {
    std::cin >> exit_code;
  }

  free(server_instance);
  MHD_stop_daemon(daemon);
  return 0;
}

int Server::ahc(void* cls, MHD_Connection* connection, 
  const char* url, const char* method,
  const char* version, const char* upload_data,
  size_t* data_size, void** con_cls) {

  if(server_instance == NULL)
    return MHD_NO;

  struct ahc_info info;
  info.cls = cls;
  info.connection = connection;
  info.url = url;
  info.method = method;
  info.version = version;
  info.data = upload_data;
  info.data_size = data_size;
  info.con_cls = con_cls;

  return server_instance->process(info);
}

}
