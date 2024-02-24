#pragma once
#include <string>
#include <regex>

std::string verifyName(std::string name);
extern std::regex pin_pattern;
extern std::regex password_pattern;