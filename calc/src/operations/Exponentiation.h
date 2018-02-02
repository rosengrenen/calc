#pragma once

#include <cmath>

#include "Operation.h"

class Exponentiation : public Operation
{
public:
  virtual double calc(double left, double right) override
  {
    return std::pow(left, right);
  }
};