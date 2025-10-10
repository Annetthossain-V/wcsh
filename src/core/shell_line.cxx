#include "shell_line.h"
#include "../format/format.h"
#include "prompt.h"
#include <readline/readline.h>
#include <extr/extr_string.h>
#include <cstdlib>
#include <spdlog/spdlog.h>
#include <readline/history.h>

void line::get_line_stdin() {
  std::string prompt = get_prompt();
  char* line = readline(prompt.c_str());

  this->tokens = extr::split_tokens_cxx(line, " ");
  this->str = line;
  std::free(line);
}

std::string& line::get_line() { 
  return std::ref(this->str); 
}

bool line::format_line() {
  try {
    format_shell_line(this->tokens);
  } catch (...) {
    spdlog::error("formatting line failed");
    return false;
  }
  return true;
}

void line::add_history() { 
  ::add_history(this->str.c_str()); 
}

line::line() { 
  rl_initialize(); 
}
