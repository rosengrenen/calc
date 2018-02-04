#pragma once

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include <utility>

#include "Expression.h"

#include "functions/Function.h"
#include "functions/Logarithm.h"
#include "functions/Root.h"

#include "operations/Operator.h"
#include "operations/Addition.h"
#include "operations/Division.h"
#include "operations/Exponentiation.h"
#include "operations/Modulo.h"
#include "operations/Multiplication.h"
#include "operations/Subtraction.h"

class Calculator
{
public:
  double calculate(const std::string& input);
  void parse(std::vector<std::string> parts, std::unique_ptr<Term>& term);
  bool isNumber(const std::string& input);
  bool isOperator(const std::string& input);
  bool isOperand(const std::string& input);
  std::vector<std::string> split(const std::string& input);
private:
  Expression expr;
  std::unordered_map<std::string, std::shared_ptr<Function>> functions = {
    { "root", std::make_shared<Root>() },
    { "log", std::make_shared<Logarithm>() }
  };
  std::unordered_map<std::string, std::pair<int, std::shared_ptr<Operator>>> operators = {
    // v-- Operator       v-- Order of operation  v-- Corresponding class
    { "+", std::make_pair(0, std::make_shared<Addition>()) },
    { "-", std::make_pair(0, std::make_shared<Subtraction>()) },
    { "*", std::make_pair(1, std::make_shared<Multiplication>()) },
    { "/", std::make_pair(1, std::make_shared<Division>()) },
    { "%", std::make_pair(1, std::make_shared<Modulo>()) },
    { "^", std::make_pair(2, std::make_shared<Exponentiation>()) },
  };
};

