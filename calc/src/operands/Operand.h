#pragma once

#include <memory>
#include <string>

class Operand
{
public:
  virtual double& calc() = 0;
};