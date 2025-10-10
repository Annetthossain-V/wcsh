#include "core/shell_line.h"
#include <spdlog/spdlog.h>
#include "var/var.h"


static void set_system_var() {
  var::make_var("$VER", "0.2");
  var::make_var("$SHELL", "wcsh");
  var::make_var("$SH", "wcsh");
}

int main(int argc, char** argv) {
  // inits and stuff
  set_system_var();

  line sh_line;
  while (true) {
    sh_line.get_line_stdin();
    sh_line.add_history();

    if (sh_line.get_line().empty()) continue;
    if (sh_line.get_line() == "exit") break;

    if (!sh_line.format_line()) continue;

    if (sh_line.intern()) {
      sh_line.intern_exec();
      continue;
    }

    sh_line.sys_exec();
    set_system_var(); // performance problem
  }

  return 0;
}
