#pragma once

class Operator
{
public:
  virtual double calc(double left, double right) = 0;
};