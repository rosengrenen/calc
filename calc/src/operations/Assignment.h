#pragma once

#include "Operator.h"

class Assignment : public Operator
{
public:
  double& calc(double& left, double& right) override
  {
    left = right;
    return right;
  }
};