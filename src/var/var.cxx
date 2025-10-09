#include "var.h"
#include <stdexcept>
#include <string>
#include <map>
#include <spdlog/spdlog.h>

static std::map<std::string, std::string> vtable;

void var::make_var(std::string name, std::string val) {
  auto [iter, status] = vtable.insert_or_assign(name, val);
  if (!status) throw std::runtime_error("failed to insert variable");
}

void var::delete_var(std::string name) {
  auto token = vtable.find(name);
  if (token != vtable.end())
    vtable.erase(token);
  else
    spdlog::error("variable `{}` not found!", name);
}

std::string var::get_val(std::string name) {
  std::string val = "";

  try {
    val = vtable.at(name);
  } catch (...) {
    spdlog::error("cannot get variable `{}`", name);
  }

  return val;
}
