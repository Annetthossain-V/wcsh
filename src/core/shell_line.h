#pragma once
#include <string>
#include <vector>

class line {
public:
  line();
  void get_line_stdin();
  bool format_line();
  void add_history();
  void sys_exec();
  bool intern();
  void intern_exec();

  std::string& get_line();
private:
  std::string str;
  std::vector<std::string> tokens;
  int exit_stat;
  bool file_open;
};
