#pragma once

#include "Term.h"

class Expression
{
public:
  std::unique_ptr<Term> term = std::make_unique<Term>();
  double evaluate()
  {
    return term->calc();
  }
};