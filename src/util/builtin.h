#pragma once
#include <string>

void builtin_cd(std::string path);
void builtin_let(std::string name, std::string val);
void builtin_alias(std::string name, std::string val);
