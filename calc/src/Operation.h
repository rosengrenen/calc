#pragma once

class Operation
{
public:
  virtual double calc(double left, double right) = 0;
};