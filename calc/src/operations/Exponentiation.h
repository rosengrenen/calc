#pragma once

#include <cmath>

#include "Operator.h"

class Exponentiation : public Operator
{
public:
  double& calc(double& left, double& right) override
  {
    this->result = std::pow(left, right);
    return this->result;
  }
};