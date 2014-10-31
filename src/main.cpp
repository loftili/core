#include "loftili.h"
#include "util/cli/parser.h"
#include "util/options.h"
#include "server.h"
#include <sys/types.h>
#include <sys/stat.h>

using namespace loftili;

int main(int argc, char * argv[]) {
  Options opts = cli::Parser::parse(argc, argv);

  if(opts.daemonize && !opts.help) {
    std::cout << "starting" << std::endl;
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

  if(!opts.help)
    return Server::run(opts);
}
