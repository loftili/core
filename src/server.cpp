#include <server.h>
#define METHOD_ERROR "<html><head><title>Illegal request</title></head><body>Go away.</body></html>"

namespace loftili {

Server* Server::server_instance;

Server::Server(Options opts) : router(), dispatch(), registration(opts) { 
  standalone = opts.standalone;
}

Server::~Server() { }

bool Server::enroll() {
  bool is_valid = registration.attempt();

  if(is_valid) {
    Credentials creds = registration.creds();
    Options opts = registration.opts();
    router.initialize(creds, opts);
  }

  return is_valid;
}

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

  bool validated = standalone ? true : dispatch.validate(request->connection);

  if(!validated)
    return dispatch.reject(request);

  int handled = router.handle(request, &response);

  // send back the final response to the client
  return dispatch.send(&response, info.connection);
}

int Server::run(Options opts) {
  if(opts.use_log) {
    LOG_STATE opened = Logger::use(opts.logfile);
    if(opened != LOG_STATE_READY)
      return 1;
  }

  Logger log("SERVER STARTUP");
  int port = opts.port;

  log.info("preparing a new server instance");
  server_instance = new Server(opts);

  if(!opts.standalone) {
    bool enrolled = server_instance->enroll();
    if(!enrolled) {
      log.info("failed device registration with server, exiting... please refer to http://loftili.com/faq");
      delete server_instance;
      return 1;
    }
  } else {
    log.info("running core server in standalone mode...");
  }

  log.info("initializing audio library");
  ao_initialize();

  log.info("starting libmicrohttp daemon on: " + std::to_string(port));
  MHD_Daemon* daemon = MHD_start_daemon(
    MHD_USE_DEBUG | MHD_USE_SELECT_INTERNALLY, port, 
    NULL, NULL, 
    &ahc, NULL,
    MHD_OPTION_NOTIFY_COMPLETED, &completion,
    NULL, MHD_OPTION_END);

  if(daemon == NULL) {
    log.fatal("Daemon unable to start successfully!");
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
