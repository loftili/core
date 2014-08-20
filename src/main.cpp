#include "loftili.h"
#include "util/cli/parser.h"
#include "util/options.h"
#include "server.h"

using namespace loftili;

int main(int argc, char * argv[]) {
  Options opts = cli::Parser::parse(argc, argv);

  if(!opts.help)
    return Server::run(opts);
}
