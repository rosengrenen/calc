#pragma once

#include "Operator.h"

class Division : public Operator
{
public:
  double& calc(double& left, double& right) override
  {
    this->result = left / right;
    return this->result;
  }
};