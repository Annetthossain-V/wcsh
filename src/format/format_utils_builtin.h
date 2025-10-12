#pragma once
#include <utility>
#include <vector>
#include <string>


std::string format_cd(std::vector<std::string>& line);
std::string format_let(std::vector<std::string>& line, std::string& name);
std::string format_alias(std::vector<std::string>& line, std::string& name);
std::string format_readf(std::vector<std::string>& line); // make this support command line arguments
std::pair<std::string, std::string> format_add(std::vector<std::string>& line);
std::vector<std::string> format_if(std::vector<std::string>& line);
