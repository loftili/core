#include <sys/types.h>
#include <sys/stat.h>
#include "loftili.h"
#include "util/cli/parser.h"
#include "server.h"

using namespace loftili;

int main(int argc, char * argv[]) {
  Configuration config = cli::Parser::parse(argc, argv);

  if(config.daemonize && !config.help) {
    std::cout << "starting as thread" << std::endl;
    pid_t pid, sid;
    pid = fork();

    if(pid < 0)
      exit(EXIT_FAILURE); 

    if(pid > 0)
      exit(EXIT_SUCCESS);

    umask(0);
    sid = setsid();

    if(sid < 0)
      exit(EXIT_FAILURE);

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
  }

  if(!config.help)
    return Server::run(config);

  return 1;
}
