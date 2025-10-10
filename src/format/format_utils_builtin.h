#pragma once
#include <vector>
#include <string>

std::string format_cd(std::vector<std::string>& line);
std::string format_let(std::vector<std::string>& line, std::string& name);
std::string format_alias(std::vector<std::string>& line, std::string& name);
