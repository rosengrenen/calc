#pragma once

#include <cmath>

#include "Operator.h"

class Modulo : public Operator
{
public:
  virtual double calc(double left, double right) override
  {
    return std::fmod(left, right);
  }
};