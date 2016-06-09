// validate.cpp
#include "../include/validate.h"

bool Validate::validate_input(std::string s) {
  if (s.find("\'") == std::string::npos && s.find("\\") == std::string::npos
      && s.find("&") == std::string::npos && s.find("=") == std::string::npos) {
    return true;
  }
  else return false;
}
