#include "cond.h"
#include "../var/var.h"
#include "../core/utility.h"
#include <string>

bool eval_cond(cond& condition, std::string& var1, std::string& var2) {
  auto val1 = var::get_val(var1);
  auto val2 = var::get_val(var2);

  if (!valid_float(val1) || !valid_float(val2)) {
    if (condition != cond::Equal && condition != cond::NotEqual)
      throw std::runtime_error("cannot compare string like this");

    switch (condition) {
      case cond::Equal:
        if (val1 == val2) return true;
        else return false;
      case cond::NotEqual:
        if (val1 != val2) return true;
        else return false;
      default:
        return false;
    }
  }

  double dval1 = std::stod(val1);
  double dval2 = std::stod(val2);

  switch (condition) {
    case cond::Equal:
      if (dval1 == dval2) return true;
      else return false;
    case cond::NotEqual:
      if (dval1 != dval2) return true;
      else return false;
    case cond::Greater:
      if (dval1 > dval2) return true;
      else return false;
    case cond::Less:
      if (dval1 < dval2) return true;
      else return false;
    case cond::GreaterOrEqual:
      if (dval1 >= dval2) return true;
      else return false;
    case cond::LessOrEqual:
      if (dval1 <= dval2) return true;
      else return false;
    default:
      throw std::runtime_error("Unknown condition");
  }

  return false;
}
