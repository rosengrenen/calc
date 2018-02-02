#pragma once

#include <vector>

class Function
{
public:
  virtual double calc() = 0;
  void addArgument(double arg)
  {
    this->arguments.push_back(arg);
  }
protected:
  std::vector<double> arguments;
};