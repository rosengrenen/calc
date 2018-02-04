#pragma once

#include <cmath>

#include "Operator.h"

class Exponentiation : public Operator
{
public:
  virtual double calc(double left, double right) override
  {
    return std::pow(left, right);
  }
};