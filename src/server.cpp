#include <server.h>

namespace loftili {

Configuration* config = 0;
Server* Server::server_instance;

Server::Server() : router(), dispatch() {
  router.initialize();
}

Server::~Server() { }

int Server::process(struct ahc_info info) {
  Request* request = static_cast<Request*>(*info.con_cls);

  Response response;

  bool is_post = strcmp(info.method, "POST") == 0;

  // first attempts are meant to handle the headers
  // only. the data comes in second
  if(request == NULL) {
    request = new Request(info);
    *info.con_cls = request;

    if(is_post)
      return MHD_NO;

    return MHD_YES;
  }

  bool validated = dispatch.validate(request->connection);

  if(!validated)
    return dispatch.reject(request);

  int handled = router.handle(request, &response);

  // send back the final response to the client
  return dispatch.send(&response, info.connection);
}

int Server::run(Configuration config) {
  Logger log("Server");

  RegistrationService registrar;
  bool registered = registrar.authenticate(&config);

  if(!registered) {
    log.info("unable to register with the server, please try again");
    return 1;
  } else {
    log.info("device is now registered with the server, continuing");
  }

  log.info("initializing application configuration");
  loftili::config = &config;

  log.info("initializing audio library");
  ao_initialize();

  log.info("preparing a new server instance");
  server_instance = new Server();

  int port = config.port;
  log.info("starting libmicrohttp daemon on: " + std::to_string(port));

  MHD_Daemon* daemon = MHD_start_daemon(
    MHD_USE_DEBUG | MHD_USE_SELECT_INTERNALLY,
    port, 
    NULL, 
    NULL, 
    &ahc, 
    NULL,
    MHD_OPTION_NOTIFY_COMPLETED,
    &completion,
    NULL, 
    MHD_OPTION_END
  );

  if(daemon == NULL) {
    log.fatal("daemon unable to start successfully!");
    return 1;
  }

  std::string exit_code = "";
  while(exit_code != "exit") {
    std::cin >> exit_code;
  }

  Logger::close();

  delete server_instance;

  MHD_stop_daemon(daemon);

  ao_shutdown();

  return 0;
}

void Server::completion(void *cls, MHD_Connection* connection, void **con_cls, MHD_RequestTerminationCode toe) {
  Request* request = (Request*) *con_cls;
  delete request;
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
