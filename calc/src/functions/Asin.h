#pragma once

#include <cmath>

#include "Function.h"

class Asin : public Function
{
public:
  double& calc() override
  {
    if (this->arguments.empty())
    {
      //TODO: error class
      throw 0;
    }
    this->result = std::asin(this->arguments.at(0));
    this->arguments.clear();
    return this->result;
  }
};