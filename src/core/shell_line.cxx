#include "shell_line.h"
#include "../format/format.h"
#include "prompt.h"
#include <readline/readline.h>
#include <cstdlib>
#include <extr/extr_string.h>
#include <unistd.h>
#include <cstdlib>
#include <sys/types.h>
#include <sys/wait.h>
#include <extr/cpp.hxx>
#include "../format/format_utils_builtin.h"
#include "../util/builtin.h"
#include <spdlog/spdlog.h>
#include <readline/history.h>

void line::get_line_stdin() {
  std::string prompt = get_prompt();
  char* line = readline(prompt.c_str());

  this->str = line;
  std::free(line);
}

std::string& line::get_line() { return std::ref(this->str); }

void line::sys_exec() {
  size_t argv_count = 0;
  char** argv = extr::split_tokens(this->str.c_str(), " ", &argv_count);
  if (argv == NULL)
    return;

  pid_t child = fork();
  if (child < 0) {
    perror("fork");
    return; //entropy
  }

  if (child == 0) {
    execvp(argv[0], argv);
    perror(argv[0]);
    std::exit(EXIT_FAILURE);
  } else {
    waitpid(child, &this->exit_stat, 0);
  }

  extr::_core_free_split_arr(argv, argv_count);
}

bool line::format_line() { 
  try {
    format_shell_line(this->str);
  } catch (...) {
    spdlog::error("formatting line failed");
    return false;
  }
  return true;
}

bool line::intern() {
  auto split = extr::split_tokens_cxx(this->str, " ");
  
  if (split[0] == "cd")
    return true;
  else if (split[0] == "let")
    return true;

 return false; 
}

void line::intern_exec() {
  auto split = extr::split_tokens_cxx(this->str, " ");

  if (split[0] == "cd") {
    try {
      auto tok = format_cd(this->str);
      builtin_cd(tok);
    } catch(...) {
      spdlog::error("parsing cd failed");
    }
  }
  else if (split[0] == "let") {
    try {
      auto tok = format_let(this->str);

      builtin_let(tok);
    } catch (...) {
      spdlog::error("unable to make variable");
    }
  }

  return;
}

void line::add_history() { ::add_history(this->str.c_str()); }

line::line() { rl_initialize(); }
