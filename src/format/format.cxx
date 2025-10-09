#include "format.h"
#include <extr/extr_string.h>
#include <stdexcept>
#include <string>
#include <vector>
#include <print>
#include <cstdlib>

static inline void replace_home(std::vector<std::string>& lines) {
  std::string home = std::getenv("HOME");
  for (auto& line : lines) {
    for (size_t pos = 0; (pos = line.find('~', pos)) != std::string::npos; ) {
      line.replace(pos, 1, home);
      pos += home.size();
    }
  }
}

static inline void replace_alias(std::vector<std::string>& lines);

void format_shell_line(std::string& line) {
  std::vector<std::string> lines = extr::split_tokens_cxx(line, " ");
  if (lines.empty()) throw std::runtime_error("unable to split line");
  
  replace_home(lines);

  line.clear();
  for (auto& ln : lines) { 
    line.append(ln); 
    line.push_back(' '); 
  }
}
