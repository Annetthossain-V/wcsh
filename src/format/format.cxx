#include "format.h"
#include <extr/extr_string.h>
#include <stdexcept>
#include <string>
#include <vector>
#include <print>

static inline void replace_home(std::vector<std::string>& lines) {}

void format_shell_line(std::string& line) {
  std::vector<std::string> lines = extr::split_tokens_cxx(line, " ");
  if (lines.empty()) throw std::runtime_error("unable to split line");
  
  for (auto& v : lines) {
    std::println("line: {}", v);
  }

}
