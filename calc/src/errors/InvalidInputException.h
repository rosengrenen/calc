#pragma once

#include "CalculatorException.h"

class InvalidInputException : public CalculatorException
{
public:
  using CalculatorException::CalculatorException;
};