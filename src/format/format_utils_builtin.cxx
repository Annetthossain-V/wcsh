#include "format_utils_builtin.h"
#include <stdexcept>
#include <string>
#include <spdlog/spdlog.h>
#include <utility>

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
    retval = val;
  } else if (tokens.size() > 4) {
    spdlog::warn("expr not supported yet");
  }

  name = tokens[1];
  return retval;
}

std::string format_alias(std::vector<std::string> &line, std::string &name) {
  if (line.size() != 3) throw std::runtime_error("invalid args for alias");
  name = line[1];
  return line[2];
}

std::string format_readf(std::vector<std::string> &line) {
  if (line.size() != 2) throw std::runtime_error("invalid args for readf");
  return line[1];
}

std::pair<std::string, std::string> format_add(std::vector<std::string> &line) {
  if (line.size() != 3) throw std::runtime_error("invalid args for add");
  return {line[1], line[2]};
}
