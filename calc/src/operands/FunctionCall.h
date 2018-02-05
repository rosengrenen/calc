#pragma once

#include <memory>

#include "Operand.h"

#include "../functions/Function.h"

class FunctionCall : public Operand
{
public:
  std::string funcName;
  std::shared_ptr<Function> func;
  virtual double calc() override
  { 
    return this->func->calc();
  }
  virtual std::string print() override
  {
    std::string output = "func(";
    auto args = this->func->getArguments();
    for (int i = 0; i < args.size(); ++i)
    {
      output += std::to_string(args.at(i));
      if (i != args.size() - 1 && i != 0)
      {
        output += ", ";
      }
    }
    return output + ")";
  }
};