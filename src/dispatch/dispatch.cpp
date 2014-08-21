#include "dispatch/dispatch.h"

namespace loftili {

Dispatch::Dispatch() { }
Dispatch::~Dispatch() { }

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
  delete res;

  // send back the MHD status
  return ret;
}

void Dispatch::headers(MHD_Response* m_res, Response* res) {
  MHD_add_response_header(m_res, "Content-type", "application/json");
}

}
