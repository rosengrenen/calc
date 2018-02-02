#pragma once

#include <cmath>

#include "Operation.h"

class Modulo : public Operation
{
public:
  virtual double calc(double left, double right) override
  {
    return std::fmod(left, right);
  }
};