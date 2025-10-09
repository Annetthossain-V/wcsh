#include "expr.h"
#include <string>
#include <vector>
#include <spdlog/spdlog.h>
#include <stdexcept>

// for now this function will not support
// more than a single operation.
// will change in the future
// #include <future>
std::string expr_assign_val(std::vector<std::string>& toks, size_t pos) {
  return "NULL";
}

bool valid_double(const std::string& s) {
  for (size_t i = 0; i < s.size(); i++) {
    char c = s[i];
    if ((c != '.' && c < '0') || (c != '.' && c > '9'))
      return false;
  }
  return true;
}
