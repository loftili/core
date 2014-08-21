#include <server.h>

namespace loftili {

Server* Server::server_instance;

Server::Server() : router(), dispatch() { 
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
  return dispatch.send(response, info.connection);
}

int Server::run(Options opts) {
  std::ofstream out(opts.logfile);
  std::streambuf *coutbuf = std::cout.rdbuf();
  std::cout.rdbuf(out.rdbuf());


  Logger log("SERVER STARTUP");
  int port = opts.port;

  log.info("preparing a new server instance");
  server_instance = new Server();

  log.info("starting libmicrohttp daemon on: " + std::to_string(port));
  MHD_Daemon* daemon = MHD_start_daemon(
    MHD_USE_DEBUG | MHD_USE_SELECT_INTERNALLY, 
    port, NULL, 
    NULL, &ahc, NULL, 
    MHD_OPTION_END);

  if(daemon == NULL) {
    log.fatal("Daemon unable to start successfully!");
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
