#pragma once
#include <string>

namespace alias {

bool find_alias(std::string name);
std::string get_alias(std::string name);
void set_alias(std::string name, std::string val);

}
