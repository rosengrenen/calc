#pragma once

#include "Operator.h"

class Multiplication : public Operator
{
public:
  virtual double calc(double left, double right) override
  {
    return left * right;
  }
};