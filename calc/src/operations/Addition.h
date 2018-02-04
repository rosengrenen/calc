#pragma once

#include "Operator.h"

class Addition : public Operator
{
public:
  virtual double calc(double left, double right) override
  {
    return left + right;
  }
};