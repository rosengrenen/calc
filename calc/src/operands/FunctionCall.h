#pragma once

#include <memory>

#include "Operand.h"

#include "../functions/Function.h"

class FunctionCall : public Operand
{
public:
  std::shared_ptr<Function> func;
  std::vector<std::unique_ptr<Operand>> args;
  virtual double calc() override
  { 
    for (auto& arg : args)
    {
      this->func->addArgument(arg->calc());
    }
    return this->func->calc();
  }
};