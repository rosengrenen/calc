#pragma once

#include "Operation.h"

class Addition : public Operation
{
public:
  virtual double calc(double left, double right) override
  {
    return left + right;
  }
};