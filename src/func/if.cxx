#include "cond.h"
#include <string>
#include <vector>
#include "../core/shell_line.h"

void if_block(std::string &var1, std::string &var2, cond condition, line& sh) {
  std::vector<std::string> insts;

  get_block(sh, "endif", insts);

  if (eval_cond(condition, var1, var2)) {
    line csh;
    for (auto& inst : insts) {
      csh = inst;
      exec_sh(csh);
    }
  }

  return;
}
