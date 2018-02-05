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
  virtual std::string print() override
  {
    // Check significant figures
    return std::to_string(value);
  }
};