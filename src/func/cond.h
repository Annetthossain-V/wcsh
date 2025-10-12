#pragma once
#include <vector>
#include <string>
#include "../core/shell_line.h"

enum cond {
  Equal, // ==
  NotEqual, // !=
  Less, // < 
  Greater, // >
  LessOrEqual, // <=
  GreaterOrEqual, // >=
};

void if_block(std::string& var1, std::string& var2, cond condition, line& sh);
