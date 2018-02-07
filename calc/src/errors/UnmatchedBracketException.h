#pragma once

#include "CalculatorException.h"

class UnmatchedBracketException : public CalculatorException
{
public:
  using CalculatorException::CalculatorException;
};