#pragma once

#include "Operation.h"

class Division : public Operation
{
public:
  virtual double calc(double left, double right) override
  {
    return left / right;
  }
};