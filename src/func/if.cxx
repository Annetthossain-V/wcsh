#include "cond.h"
#include <stdexcept>
#include <vector>
#include "../core/shell_line.h"
#include "../core/utility.h"
#include "../var/var.h"

static bool eval_cond(cond& condition, auto& var1, auto& var2) {
  auto val1 = var::get_val(var1);
  auto val2 = var::get_val(var2);

  if (!valid_float(val1) || !valid_float(val2)) {
    if (condition != cond::Equal && condition != cond::NotEqual) 
      throw std::runtime_error("cannot compare string like this");
  }

  return false;
}

void if_block(std::string &var1, std::string &var2, cond condition, line& sh) {
  std::vector<std::string> insts;

  sh.block_prompt = true;
  while (true) {
    sh.get_line_io();
    if (sh.get_line() == "endif") break;

    insts.push_back(sh.get_line());
  }
  sh.block_prompt = false;

  if (eval_cond(condition, var1, var2)) {

  }
}
