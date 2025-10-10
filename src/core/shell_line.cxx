#include "shell_line.h"
#include "../format/format.h"
#include "prompt.h"
#include <readline/readline.h>
#include <extr/extr_string.h>
#include <cstdlib>
#include <spdlog/spdlog.h>
#include <readline/history.h>
#include <fstream>

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
  this->file_mode = false;
  this->file_eof = false;
}

line::~line() {
  if (this->file.is_open())
    this->file.close();
}

void line::get_line_io() {
  if (this->file_mode) {
    if (this->file.eof()) {
      this->file_eof = true;
      return;
    }
    std::getline(this->file, this->str);
  } else {
    char* ln = readline("> ");
    this->str = ln;
    std::free(ln);
  }

  this->tokens = extr::split_tokens_cxx(this->str, " ");
}

void line::open_file(std::string name) {
  this->file_mode = true;
  this->file.open(name);
  if (!this->file.is_open()) throw std::runtime_error("Failed to open file");
}

line& line::operator=(const std::string line) {
  this->str = line;
  this->tokens = extr::split_tokens_cxx(this->str, " ");
  return *this;
}
