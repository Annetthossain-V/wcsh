#include "shell_line.h"
#include "prompt.h"
#include <readline/readline.h>
#include <cstdlib>
#include <extr/extr_string.h>
#include <unistd.h>
#include <cstdlib>
#include <sys/types.h>
#include <sys/wait.h>

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
  size_t argv_count = 0;
  char** argv = extr::split_tokens(this->line.c_str(), " ", &argv_count);
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
