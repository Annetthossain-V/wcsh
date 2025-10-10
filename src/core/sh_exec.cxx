#include "shell_line.h"
#include <unistd.h>
#include <cstdlib>
#include <sys/types.h>
#include <sys/wait.h>
#include <spdlog/spdlog.h>
#include <extr/extr_string.h>
#include <print>

void line::sys_exec() {
  char** argv = (char**) std::malloc((this->tokens.size() + 1) * sizeof(char*));
  size_t argv_count = 0;
  for (size_t i = 0; i < this->tokens.size(); i++) {
    argv[i] = (char*) malloc(strlen(this->tokens[i].c_str()) + 1);
    strcpy(argv[i], tokens[i].c_str());
  }
  argv_count = tokens.size();
  argv[tokens.size()] = nullptr;

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
