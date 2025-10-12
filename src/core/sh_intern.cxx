#include "shell_line.h"
#include <cstdlib>
#include "../format/format_utils_builtin.h"
#include "../util/builtin.h"
#include <spdlog/spdlog.h>


bool line::intern() {
  if (this->tokens[0] == "cd")
    return true;
  else if (this->tokens[0] == "let")
    return true;
  else if (this->tokens[0] == "alias")
    return true;
  else if (this->tokens[0] == "readf")
    return true;
  else if (this->tokens[0] == "add")
    return true;
  else if (this->tokens[0] == "if")
    return true;

 return false;
}

void line::intern_exec() {
  if (this->tokens[0] == "cd") {
    try {
      auto tok = format_cd(this->tokens);
      builtin_cd(tok);
    } catch(...) {
      spdlog::error("parsing cd failed");
    }
  }

  else if (this->tokens[0] == "let") {
    try {
      std::string name = "";
      auto tok = format_let(this->tokens, name);
      builtin_let(name, tok);
    } catch (...) {
      spdlog::error("unable to make variable");
    }
  }

  else if (this->tokens[0] == "alias") {
    try {
      std::string name = "h";
      auto tok = format_alias(this->tokens, name);
      builtin_alias(name, tok);
    } catch (...) {
      spdlog::error("unable to set alias");
    }
  }

  else if (this->tokens[0] == "readf") {
    try {
      auto name = format_readf(this->tokens);
      builtin_readf(name);
    } catch (...) {
      spdlog::error("unable to read file");
    }
  }
  else if (this->tokens[0] == "add") {
    try {
      auto [v1, v2] = format_add(this->tokens);
      builtin_add(v1, v2);
    } catch (...) {
      spdlog::error("unable to add");
    }
  }

  else if (this->tokens[0] == "if") {
    try {
      auto parsed_if = format_if(this->tokens);
      builtin_if(parsed_if, *this);
    } catch (...) {
      spdlog::error("`if` failed");
    }
  }

  return;
}
