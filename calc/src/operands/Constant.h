#pragma once

#include <memory>

#include "Operand.h"

class Constant : public Operand
{
public:
  double value;
  Constant(double value) : value(value)
  { }
  virtual double calc() override
  {
    return this->value;
  }
};