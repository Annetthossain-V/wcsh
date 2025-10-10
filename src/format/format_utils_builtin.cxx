#include "format_utils_builtin.h"
#include <stdexcept>
#include <string>
#include <spdlog/spdlog.h>

std::string format_cd(std::vector<std::string>& line) {
  if (line.empty()) throw std::runtime_error("tokens empty");

  if (line.size() != 2) {
    spdlog::error("invalid arguments for cd");
    throw std::runtime_error("error format_cd");
  }

  return line[1];
}

std::string format_let(std::vector<std::string>& line, std::string& name) {
  auto& tokens = line;
  std::string retval = "";
  if (tokens.empty()) throw std::runtime_error("tokens empty");

  if (tokens.size() < 4) {
    spdlog::error("not enough arguments given for `let`");
    throw std::runtime_error("error let");
  }

  if (tokens[2] != "=") {
    spdlog::error("missing assignment operator");
    throw std::runtime_error("variable must be initialized");
  }

  if (tokens.size() == 4) {
    auto val = tokens[3];

    if (val.size() == 1) {
      char v = val[0];
      switch(v) {
        case '*':
        case '/':
        case '+':
        case '-':
        case '=':
          throw std::runtime_error("cannot assign token to variable");
      }
    }
    retval = val;
  } else if (tokens.size() > 4) {
    spdlog::warn("expr not supported yet");
  }

  name = tokens[1];
  return retval;
}
