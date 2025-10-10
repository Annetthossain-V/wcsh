#include "alias.h"
#include <map>
#include <string>
#include <spdlog/spdlog.h>

static std::map<std::string, std::string> alias_db;

bool alias::find_alias(std::string name) {
  return alias_db.contains(name);
}

std::string alias::get_alias(std::string name) {
  std::string retval = "";

  try {
    retval = alias_db.at(name);
  } catch (...) {
    spdlog::error("unable to find alias for {}", name);
    retval = name;
  }
  
  return retval;
}

void alias::set_alias(std::string name, std::string val) {
  alias_db.insert_or_assign(name, val);
}
