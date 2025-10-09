#include "builtin.h"
#include <string>
#include <unistd.h>
#include <spdlog/spdlog.h>

void builtin_cd(std::string path) {
 if (chdir(path.c_str()) != 0) {
   spdlog::error("cannot find `{}`", path);
   throw std::runtime_error("error cd");
 }
}
