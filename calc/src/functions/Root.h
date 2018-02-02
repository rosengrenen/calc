#pragma once

#include <cmath>

#include "Function.h"

class Root : public Function
{
public:
  virtual double calc() override
  {
    double value;
    double degree = 2;
    if (this->arguments.size() > 0)
    {
      value = this->arguments.at(0);
      if (this->arguments.size() > 1)
      {
        degree = this->arguments.at(1);
      }
    }
    else if (this->arguments.empty())
    {
      //TODO: error class
      throw 0;
    }
    return std::pow(value, 1.0 / degree);
  }
};