#pragma once
#include <string>
#include <vector>

namespace var {

void make_var(std::string name, std::string val);
void delete_var(std::string name);
std::string get_val(std::string name);

}
