#include "format_utils_builtin.h"
#include <stdexcept>
#include <string>
#include <extr/extr_string.h>
#include <spdlog/spdlog.h>

std::string format_cd(std::string line) {
  auto tokens = extr::split_tokens_cxx(line, " ");
  if (tokens.empty()) throw std::runtime_error("tokens empty");
  
  if (tokens.size() != 2) {
    spdlog::error("invalid arguments for cd");
    throw std::runtime_error("error format_cd");
  }

  return tokens[1];
} 
