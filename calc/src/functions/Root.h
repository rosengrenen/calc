#pragma once

#include <cmath>

#include "Function.h"

class Root : public Function
{
public:
  virtual double calc() override
  {
    double value;
    double n = 2;
    if (this->arguments.empty())
    {
      //TODO: error class
      throw 0;
    }
    else
    {
      value = this->arguments.at(0);
      if (this->arguments.size() > 1)
      {
        n = this->arguments.at(1);
      }
    }
    this->arguments.clear();
    return std::pow(value, 1.0 / n);
  }
};