#include "shell_line.h"
#include "prompt.h"
#include <readline/readline.h>
#include <cstdlib>
#include <extr/extr_string.h>

void line::get_line_stdin() {
  std::string prompt = get_prompt();
  char* line = readline(prompt.c_str());

  this->line = line;
  std::free(line);
}

std::string& line::get_line() {
  return std::ref(this->line);
}

void line::sys_exec() {
  
}
