#pragma once
#include <string>

class line {
public:  
  void get_line_stdin();
  void format_line();
  void add_history();
  void sys_exec();
  bool intern();
  void intern_exec();

  std::string& get_line();
private:
  std::string line;
  int exit_stat;
};
