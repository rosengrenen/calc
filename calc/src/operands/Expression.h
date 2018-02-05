#pragma once

#include <memory>

#include "Operand.h"

#include "../operations/Operator.h"

class Expression : public Operand
{
public:
  std::string operatorName;
  std::unique_ptr<Operand> left;
  std::unique_ptr<Operand> right;
  std::shared_ptr<Operator> opr;
  virtual double calc() override
  {
    return this->opr->calc(this->left->calc(), this->right->calc());
  }
  virtual std::string print() override
  {
      return "(" + this->left->print() + "+" + this->right->print() + ")";
  }
};