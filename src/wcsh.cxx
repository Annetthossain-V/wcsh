#include "core/shell_line.h"
#include <spdlog/spdlog.h>

// keeping main very simple
int main(int argc, char** argv) {
  // inits and stuff

  line sh_line;
  while (true) {
    sh_line.get_line_stdin();

    if (sh_line.get_line() == "exit") break;
    if (sh_line.get_line().empty()) continue;

    sh_line.format_line();

    sh_line.sys_exec();
  }

  return 0;
}
