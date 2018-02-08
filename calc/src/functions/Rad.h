#pragma once

#include <cmath>

#include "../Constants.h"
#include "Function.h"

class Rad : public Function
{
public:
  double& calc() override
  {
    if (this->arguments.empty())
    {
      //TODO: error class
      throw 0;
    }
    this->result = this->arguments.at(0) * Constants::pi / 180.0;
    this->arguments.clear();
    return this->result;
  }
};