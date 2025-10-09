#pragma once
#include <string>
#include <vector>

std::string expr_assign_val(std::vector<std::string>& toks, size_t pos);

bool valid_double(const std::string& s);
