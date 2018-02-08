#pragma once

#include <cmath>

#include "../Constants.h"
#include "Function.h"

class Deg : public Function
{
public:
  double& calc() override
  {
    if (this->arguments.empty())
    {
      //TODO: error class
      throw 0;
    }
    this->result = this->arguments.at(0) * 180.0 / Constants::pi;
    this->arguments.clear();
    return this->result;
  }
};