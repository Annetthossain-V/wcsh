#include "format.h"
#include <extr/extr_string.h>
#include <stdexcept>
#include <string>
#include <vector>
#include <print>
#include <cstdlib>
#include "../var/var.h"
#include "../var/alias.h"
#include <extr/extr_string.h>
#include <print>

static void replace_home(std::vector<std::string>& lines) {
  std::string home = std::getenv("HOME");
  for (auto& line : lines) {
    for (size_t pos = 0; (pos = line.find('~', pos)) != std::string::npos; ) {
      line.replace(pos, 1, home);
      pos += home.size();
    }
  }
}

static void replace_alias(std::vector<std::string>& lines) {
  if (alias::find_alias(lines[0])) {
    auto alias = alias::get_alias(lines[0]);
    auto tok_alias = extr::split_tokens_cxx(alias, " ");

    lines.erase(lines.begin());
    lines.insert(lines.begin(), tok_alias.begin(), tok_alias.end());
  }
}

static void replace_variable(std::vector<std::string>& lines) {
  for (size_t i = 0; i < lines.size(); i++) {
    if (lines[i][0] != '$') continue;
   
    auto val = var::get_val(lines[i]);
    lines[i] = val;
  }
}

void format_shell_line(std::vector<std::string>& lines) {
  if (lines.empty()) throw std::runtime_error("unable to split line");

  replace_home(lines);
  replace_variable(lines);
  replace_alias(lines);
}
