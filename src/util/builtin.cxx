#include "builtin.h"
#include <stdexcept>
#include <string>
#include <unistd.h>
#include <spdlog/spdlog.h>
#include "../var/var.h"
#include "../var/alias.h"
#include "../core/shell_line.h"
#include <print>
#include <utility>
#include "../core/utility.h"

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

static void get_var2_double(std::string& v1, std::string& v2, double& d1, double& d2) {
  auto str1 = var::get_val(v1);
  auto str2 = var::get_val(v2);

  if (!valid_float(str1)) {
    spdlog::error("arg1 must be a valid number");
    throw std::runtime_error("NAN"); 
  }
  if (!valid_float(str2)) {
    spdlog::error("arg2 must a valid number");
    throw std::runtime_error("NAN");
  }

  d1 = std::stod(str1);
  d2 = std::stod(str2);
}

void builtin_add(std::string v1, std::string v2) {
  v1.insert(0, 1, '$');
  v2.insert(0, 1, '$');

  double val1 = 0;
  double val2 = 0;
  get_var2_double(v1, v2, val1, val2);

  double result = val1 + val2;
  var::make_var(v1, std::to_string(result));
}
