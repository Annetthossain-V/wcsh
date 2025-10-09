#include "format_utils_builtin.h"
#include <stdexcept>
#include <string>
#include <extr/extr_string.h>
#include <spdlog/spdlog.h>
#include "expr.h"

void format_cd(std::vector<std::string>& line) {
  auto tokens = extr::split_tokens_cxx(line, " ");
  if (tokens.empty()) throw std::runtime_error("tokens empty");

  if (tokens.size() != 2) {
    spdlog::error("invalid arguments for cd");
    throw std::runtime_error("error format_cd");
  }

  return tokens[1];
}

void format_let(std::vector<std::string>& line) {
  auto tokens = extr::split_tokens_cxx(line, " */+-=");
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

    return val;
  } else if (tokens.size() > 4) {
    auto val = expr_assign_val(tokens, 3);
    return val;
  }

  return "";
}
