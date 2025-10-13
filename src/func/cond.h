#pragma once
#include <cstdlib>
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

bool eval_cond(cond& condition, std::string& var1, std::string& var2);

static inline void get_block(line& sh, const char* end_kw, auto& insts) {
  sh.block_prompt = true;
  while (true) {
    sh.get_line_io();
    if (sh.get_line() == end_kw) break;
    insts.push_back(sh.get_line());
  }
  sh.block_prompt = false;
}

static inline void exec_sh(line& sh) {
  if (sh.get_line().empty()) return;
  if (sh.get_line() == "exit") std::exit(EXIT_SUCCESS);
  if (!sh.format_line()) return;

  if (sh.intern()) {
    sh.intern_exec();
    return;
  }

  sh.sys_exec();
}

void if_block(std::string& var1, std::string& var2, cond condition, line& sh);
