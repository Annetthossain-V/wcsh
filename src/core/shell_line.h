#pragma once
#include <string>
#include <vector>
#include <fstream>

class line {
public:
  line();
  ~line();
  void get_line_stdin();
  bool format_line();
  void add_history();
  void sys_exec();
  bool intern();
  void intern_exec();
  void get_line_io();
  void open_file(std::string name);

  line& operator=(const std::string line);
  std::string& get_line();
  bool file_eof;
  bool block_prompt;
private:
  std::string str;
  std::vector<std::string> tokens;
  std::ifstream file;
  bool file_mode;
  int exit_stat;
};
