#pragma once
#include <string>
#include <vector>
#include "../core/shell_line.h"

void builtin_cd(std::string path);
void builtin_let(std::string name, std::string val);
void builtin_alias(std::string name, std::string val);
void builtin_readf(std::string name);
void builtin_add(std::string v1, std::string v2);
void builtin_if(std::vector<std::string>& block, line& sh);
void builtin_import(std::string local, std::string global);
void builtin_export(std::string global, std::string local);
void builtin_delete(std::string& name);
