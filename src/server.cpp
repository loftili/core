#include <server.h>

namespace loftili {

Server* Server::server_instance;

Server::Server() : router() { 
}

Server::~Server() { }

int Server::process(struct ahc_info info) {
  Request* request = static_cast<Request*>(*info.con_cls);

  // first attempts are meant to handle the headers
  // only. the data comes in second
  if(request == NULL) {
    request = new Request(info.url, info.method);
    *info.con_cls = request;
    return MHD_YES;
  }

  Response* response = new Response();

  int handled = router.handle(request, response);

  // the request is no longer needed now - clean it up
  delete request;
  
  // send back the final response to the client
  return queueResponse(response, info.connection);
}

int Server::queueResponse(Response* response, MHD_Connection* connection) {
  int length = response->length;
  void* data = response->content;
  int status = response->status;

  struct MHD_Response* m_response;
  m_response = MHD_create_response_from_buffer(length, data, MHD_RESPMEM_MUST_COPY);
  MHD_add_response_header(m_response, "Content-type", "application/json");
  int ret = MHD_queue_response(connection, status, m_response);

  // cleanup
  MHD_destroy_response(m_response);
  delete response;

  // send back the MHD status
  return ret;
}

int Server::run() {
  server_instance = new Server();

  MHD_Daemon* daemon = MHD_start_daemon(
    MHD_USE_DEBUG | MHD_USE_SELECT_INTERNALLY, 
    LOFTILI_DEFAULT_PORT, NULL, 
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

  delete server_instance;
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
