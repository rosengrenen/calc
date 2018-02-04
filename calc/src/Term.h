#pragma once

#include <memory>

#include "operations/Operator.h"

class Term
{
public:
  std::unique_ptr<Term> left;
  std::unique_ptr<Term> right;
  std::shared_ptr<Operator> opr;
  double calc()
  {
    return this->opr->calc(left->calc(), right->calc());
  }
};