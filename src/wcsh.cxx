#include "core/shell_line.h"
#include <spdlog/spdlog.h>

int main(int argc, char** argv) {
  // inits and stuff

  line sh_line;
  while (true) {
    sh_line.get_line_stdin();
    if (sh_line.get_line() == "exit") break;

    sh_line.sys_exec();
  }

  return 0;
}
