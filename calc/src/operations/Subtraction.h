#pragma once

#include "Operation.h"

class Subraction : public Operation
{
public:
  virtual double calc(double left, double right) override
  {
    return left - right;
  }
};