#include "builtin.h"
#include <stdexcept>
#include <string>
#include <unistd.h>
#include <spdlog/spdlog.h>
#include "../var/var.h"
#include "../var/alias.h"
#include "../core/shell_line.h"
#include <print>

void builtin_cd(std::string path) {
 if (chdir(path.c_str()) != 0) {
   spdlog::error("cannot find `{}`", path);
   throw std::runtime_error("error cd");
 }
}

void builtin_let(std::string name, std::string val) {
  name.insert(0, 1, '$');
  var::make_var(name, val);
}

void builtin_alias(std::string name, std::string val) {
  alias::set_alias(name, val);
}

void builtin_readf(std::string name) {
  line codes;
  try {
    codes.open_file(name);
  } catch (const std::runtime_error& e) {
    spdlog::error("unable to open file `{}`", name);
    return;
  }

  while (!codes.file_eof) {
    codes.get_line_io();

    if (codes.file_eof) break;
    if (codes.get_line().empty()) continue;
    if (codes.get_line() == "exit") break;

    if (!codes.format_line()) {
      std::println("line `{}`", codes.get_line());
      spdlog::error("unable to format line");
      break;
    }
    
    if (codes.intern()) {
      codes.intern_exec();
      continue;
    }

    codes.sys_exec();
  }
}
