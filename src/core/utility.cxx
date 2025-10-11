#include "utility.h"
#include <string>

bool valid_float(std::string& str) {
  for (auto c : str) {
    if ((c != '.' && c < '0') || (c != '.' && c > '9'))
      return false;
  }
  return true;
}
