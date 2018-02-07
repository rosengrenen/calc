#pragma once

#include <memory>

#include "Operand.h"

class Constant : public Operand
{
public:
  Constant(double& value, bool) : value(value)
  { }
  Constant(double value) : value(this->placeholder), placeholder(value)
  { }
  double& calc() override
  {
    return this->value;
  }
private:
  double& value;
  double placeholder;
};