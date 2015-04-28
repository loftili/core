#include "loftili.h"
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <cerrno>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <iostream>
#include <sstream>
#include <memory>

namespace loftili {

class Stream { 
  public:
    virtual ~Stream() {};
    virtual Stream& operator <<(const char *data) = 0;
};

class Socket {
  public: 
    Socket() {
      m_ref = new SocketRef();
      m_ref->m_count = 1;
    };

    Socket(const Socket& other) {
      m_ref = other.m_ref;
      m_ref->m_count++;
    };

    Socket& operator=(const Socket& other) {
      if(--m_ref->m_count < 1) delete m_ref;
      m_ref = other.m_ref;
      m_ref->m_count++;
      return *this;
    };

    int Write(const char* msg, const int length) { return m_ref->Write(msg, length); };

    bool Ok() { return m_ref->Ok(); }

    const char* Read() { return m_ref->Read(); };
    void Read(Stream *s) { return m_ref->Read(s); };

    int Connect(const char *hostname, int port) { return m_ref->Connect(hostname, port); };

    ~Socket() {
      if(--m_ref->m_count < 1) delete m_ref;
    };

  private:
    class SocketRef {
      friend Socket;
      public:
        SocketRef() : m_count(0), m_ok(false) {
          m_socket = socket(AF_INET, SOCK_STREAM, 0);
        };

        int Connect(const char *hostname, int port) {
          hostent *he = gethostbyname(hostname);
          sockaddr_in sa;

          if(he == NULL) { m_ok = false; return -1; }

          memset(&sa, 0, sizeof(sa));
          sa.sin_family = AF_INET;
          sa.sin_port = htons(port);
          sa.sin_addr.s_addr = *(long *)he->h_addr;

          int result = connect(m_socket, (sockaddr*)&sa, sizeof(sa));

          if(result < 0) { m_ok = false; return -1; }

          m_ok = true;

          return 1;
        };

        bool Ok() { return m_ok; }

        int Write(const char* msg, const int length) {
          printf("-- writing:\n%s\n-- length[%d]\n", msg, length);
          int size = send(m_socket, msg, length, 0);
          if(size != length) { m_ok = false; return -1; }
          return 0;
        };

        void Read(Stream *s) {
          int size = 2048, received;

          char buffer[size];

          // read into temporary buffer
          received = recv(m_socket, buffer, size - 1, 0);

          if(received <= 0) { m_ok = false; }

          // send buffer into stream
          (*s) << buffer;
        };

        const char* Read() {
          int size = 2048, received;
          return "";
        };

        ~SocketRef() { 
          if(m_socket) {
            printf("closing socket\n"); 
            close(m_socket); 
          }
        };

      private:
        bool m_ok;
        int m_count;
        int m_socket;
    };

    SocketRef* m_ref;
};

class Request {
  public:
    Request(std::string method="GET", std::string path="/sk") : m_method(method), m_path(path) {
      Format();
    };

    int Length() {
      return m_content.length();
    };

    Request& operator=(const Request& other) {
      m_method = other.m_method;
      m_path = other.m_path;
      return *this;
    };

    operator const char*() {
      return m_content.c_str();
    };

  private:
    void Format() {
      m_content =  m_method + " " + m_path + " HTTP/1.1\n";
      m_content += "Connection: keep-alive\n\n";
    }

    std::string m_content;
    std::string m_method;
    std::string m_path;
};

class CommandStream : public Stream {

  public:
    CommandStream() : m_data("") {
    };

    CommandStream& operator<<(const char *data) {
      std::string str = data;
      m_data += str;
      return *this;
    };

    CommandStream(CommandStream& other) {
    };

    operator const char*() {
      return m_data.c_str();
    };

    CommandStream& operator=(CommandStream& other) {
      return *this;
    };

    ~CommandStream() {
      printf("deleting\n");
    };

    private:
      std::string m_data;
};

class Command {
  public:
    Command() { };

    Command(const char *data) { };

    virtual int Execute() = 0;
    virtual ~Command() { };
};

class AudioCommand : public Command {
  public:
    int Execute() {
      printf("executing audio command\n");
      return 1;
    }
};

class GeneralCommand : public Command {
  public:
    GeneralCommand() : m_cmd(0) { };

    int Execute() { return 0; };

    GeneralCommand(const char* data) {
      printf("[%s]", data);
      m_cmd = new AudioCommand();
    };

    Command* Transform() {
      Command* m = m_cmd;
      m_cmd = 0;
      return m;
    };

    ~GeneralCommand() {
      if(m_cmd) delete m_cmd;
    };

  private:
    Command* m_cmd;
};

class Engine {
  public:
    Engine() : m_socket(new Socket) {
    };

    ~Engine() {
      delete m_socket;
    };

    int Run() {
      m_socket->Connect("127.0.0.1", 1337);
      Request r("GET", "/devicestream/open?sn=aasdasdasdasdasdasdasdasdasdasdasdasdasd");
      m_socket->Write(r, r.Length());
      Stream* s = new CommandStream();
      Command* cmd;
      int continuing = 1;

      while(continuing && m_socket->Ok()) {
        m_socket->Read(s);
        const char* d = *((CommandStream*)s);
        GeneralCommand gc = d;
        if(!(cmd = gc.Transform())) continue;
        delete s;
        s = new CommandStream();
        continuing = cmd->Execute();
      }

      delete s;
      return 0;
    };

  private:
    Socket* m_socket;
};

}

int main(int argc, char* argv[]) {
  std::unique_ptr<loftili::Engine> p1(new loftili::Engine);
  return p1->Run();
  /*
  loftili::Socket s;
  int result;

  result = s.Connect("127.0.0.1", 1337);
  if(result < 0) return result;

  loftili::Message m = "GET /sk HTTP/1.1\nConnection: Keep-alive\n\n";
  result = s.Write(m.c_str(), m.length());
  if(result < 0) return result;

  printf("attempting to read...\n");
  const char* response = s.Read();

  return 0;
  */
}
