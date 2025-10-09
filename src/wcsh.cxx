#include "core/shell_line.h"
#include <spdlog/spdlog.h>

// keeping main very simple
int main(int argc, char** argv) {
  // inits and stuff

  line sh_line;
  while (true) {
    sh_line.get_line_stdin();
    sh_line.add_history();

    if (sh_line.get_line() == "exit") break;
    if (sh_line.get_line().empty()) continue;

    if (!sh_line.format_line()) continue;

    if (sh_line.intern()) {
      sh_line.intern_exec();
      continue;
    }

    sh_line.sys_exec();
  }

  return 0;
}
