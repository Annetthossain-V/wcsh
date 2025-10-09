#include "builtin.h"
#include <string>
#include <unistd.h>
#include <spdlog/spdlog.h>
#include "../var/var.h"

void builtin_cd(std::string path) {
 if (chdir(path.c_str()) != 0) {
   spdlog::error("cannot find `{}`", path);
   throw std::runtime_error("error cd");
 }
}

void builtin_let(std::string name, std::string val) {
  var::make_var(name, val);
}
