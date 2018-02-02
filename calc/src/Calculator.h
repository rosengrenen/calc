#pragma once

#include <string>

class Calculator
{
public:
  void calculate(const std::string& input);
  double parse(const std::string& input);
  bool isNumber(const std::string& input);
};

