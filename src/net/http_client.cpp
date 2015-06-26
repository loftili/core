#include "net/http_client.h"

namespace loftili {

namespace net {

bool HttpClient::Send(HttpRequest& req) {
  bool is_ssl = req.Url().Protocol() == "https";
  TcpSocket socket(is_ssl);


  int port = req.Url().Port() > 0 ? req.Url().Port() : (is_ssl ? 443 : 80);
  int result = socket.Connect(req.Url().Host().c_str(), port);

  if(result < 0)
    return false;

  std::string request_string(req);

  result = socket.Write(request_string.c_str(), request_string.size());

  if(result < 0) 
    return false;

  if(m_parser << socket)
    m_responses.push_back(std::shared_ptr<loftili::net::HttpResponse>(new loftili::net::HttpResponse(m_parser.Data())));

  return m_responses.size() == 1;
};

std::shared_ptr<loftili::net::HttpResponse> HttpClient::Latest() {
  return m_responses.front();
}

}

}
