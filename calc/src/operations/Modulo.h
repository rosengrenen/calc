#pragma once

#include <cmath>

#include "Operator.h"

class Modulo : public Operator
{
public:
  double& calc(double& left, double& right) override
  {
    this->result = std::fmod(left, right);
    return this->result;
  }
};