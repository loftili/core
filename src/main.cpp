#include <microhttpd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
using namespace std;

#define PAGE "<html><head><title>libmicrohttpd demo</title>"\
             "</head><body>libmicrohttpd demo</body></html>"

static int ahc_echo(
    void* cls, 
    MHD_Connection* connection, 
    const char* url, 
    const char* method, 
    const char* version, 
    const char* upload_data, 
    size_t* data_size, 
    void** ptr) {

  int ret = 0;
  const char * page = static_cast<char*>(cls);
  struct MHD_Response * response;
  
  *ptr = NULL; /* clear context pointer */
  response = MHD_create_response_from_data(strlen(page), (void*) page, MHD_NO, MHD_NO);
  ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
  MHD_destroy_response(response);
  return ret;
}

int main(int argc, char ** argv) {
  struct MHD_Daemon * d;

  if (argc != 2) {
    printf("%s PORT\n", argv[0]);
    return 1;
  }

  void* html = const_cast<char*>(PAGE);

  d = MHD_start_daemon(MHD_USE_THREAD_PER_CONNECTION | MHD_USE_DEBUG,
		       atoi(argv[1]),
		       NULL,
		       NULL,
		       &ahc_echo,
		       html,
		       MHD_OPTION_END);

  if (d == NULL) {
    printf("unable to start\n");
    return 1;
  }

  string a;
  cin >> a;

  MHD_stop_daemon(d);
  return 0;
}
