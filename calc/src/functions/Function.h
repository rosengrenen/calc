#pragma once

#include <vector>

class Function
{
public:
  Function() = default;
  virtual double calc() = 0;
  void addArgument(double arg)
  {
    this->arguments.push_back(arg);
  }
  auto getArguments() const
  {
    return this->arguments;
  }
protected:
  std::vector<double> arguments;
};