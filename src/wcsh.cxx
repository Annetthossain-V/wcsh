#include "core/shell_line.h"
#include <spdlog/spdlog.h>
#include "var/var.h"
#include <extr/cmdline.h>
#include <stdexcept>
#include <csignal>
#include <print>

static void set_system_var() {
  var::make_var("$VER", "0.3");
  var::make_var("$SHELL", "wcsh");
  var::make_var("$SH", "wcsh");
}

int main(int argc, char** argv) {
  extr::args_t* args = extr::parse_args(argc, (const char**)argv, nullptr, 0); 
  if (args->files_len > 0 || args->options_len > 0) throw std::runtime_error("args not supported");

  std::signal(SIGINT, SIG_IGN);
  set_system_var();

  line sh;
  while (true) {
    sh.get_line_stdin();
    sh.add_history();

    if (sh.get_line().empty()) continue;
    if (sh.get_line() == "exit") break;

    if (!sh.format_line()) continue;

    if (sh.intern()) {
      sh.intern_exec();
      continue;
    }

    sh.sys_exec();
    set_system_var(); // performance problem
  }

  extr::close_args(args);
  return 0;
}
