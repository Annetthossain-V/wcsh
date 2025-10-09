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
  if (toks[pos + 1].size() != 1) {
    spdlog::error("unable to expr operator");
    throw std::runtime_error("invalid operator");
  }
  if (toks.size() < pos + 3) {
    spdlog::error("invalid args");
    throw std::runtime_error("invalid args");
  }

  auto& val = toks[pos];
  char op = toks[pos + 1][0];
  auto& pow = toks[pos + 2];
  std::string retval = "";

  if (valid_double(val)) {
    if (!valid_double(pow)) {
      spdlog::error("pow must be valid number for number arith operation");
      throw std::runtime_error("NAN");
    }

    double pw = std::stod(pow);
    double va = std::stod(val);
    switch (op) {
      case '*':
        va *= pw;
        break;
      case '+':
        va += pw;
        break;
      case '-':
        va -= pw;
        break;
      case '/':
        va /= pw;
        break;
      default:
        spdlog::error("unknown operator `{}`", op);
        throw std::runtime_error("unknown op");
    }

    retval = std::to_string(va);
  } else {
    switch (op) {
      case '+':
        val.append(pow);
        break;
      default:
        spdlog::error("operator `{}` not supported for string", op);
        throw std::runtime_error("unsupported op");
    }

    retval = val;
  }

  return retval;
}

bool valid_double(const std::string& s) {
  for (size_t i = 0; i < s.size(); i++) {
    char c = s[i];
    if (c != '.' && c < '0' || (c != '.' && c > '9'))
      return false;
  }
  return true;
}
