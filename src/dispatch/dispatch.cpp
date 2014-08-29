#include "dispatch/dispatch.h"

namespace loftili {

Dispatch::Dispatch() : log("Dispatch"), auth() { 
}

Dispatch::~Dispatch() {
}

bool Dispatch::validate(MHD_Connection* connection) {
  const char* auth_val = MHD_lookup_connection_value(connection, MHD_HEADER_KIND, HEADER_LOFTILI_AUTH);
  if(auth_val != NULL) {
    log.info("loftili auth header found: " + std::string(auth_val));
    return auth.validate(auth_val);
  } else {
    return false;
  }
}

int Dispatch::reject(Request* req, MHD_Connection* connection) {
  delete req;
  Response* res = new Response(HTTP_NO_AUTH);
  return send(res, connection);
}

int Dispatch::send(Response* res, MHD_Connection* connection) {
  int length = res->length;
  void* data = res->content;
  int status = res->status;

  struct MHD_Response* m_res;
  m_res = MHD_create_response_from_buffer(length, data, MHD_RESPMEM_MUST_COPY);

  headers(m_res, res);

  int ret = MHD_queue_response(connection, status, m_res);

  // cleanup
  MHD_destroy_response(m_res);

  // send back the MHD status
  return ret;
}

void Dispatch::headers(MHD_Response* m_res, Response* res) {
  HttpHeaders::const_iterator it = res->headers.begin();
  for(it; it != res->headers.end(); ++it)
    MHD_add_response_header(m_res, it->first.c_str(), it->second.c_str());
}

}
