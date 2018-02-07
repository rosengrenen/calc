#pragma once

#include "Operator.h"

class Addition : public Operator
{
public:
  double& calc(double& left, double& right) override
  {
    this->result = left + right;
    return this->result;
  }
};