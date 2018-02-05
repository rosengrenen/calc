#pragma once

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include <utility>

#include "operands/Operand.h"

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

struct OperatorRule
{
  bool unary;
  int order;
  std::shared_ptr<Operator> opr;
};

class Calculator
{
public:
  double calculate(std::string input);
  void parse(std::vector<std::string> parts, std::unique_ptr<Operand>& term);
  std::vector<std::string> split(std::string input);
private:
  std::unique_ptr<Operand> expression;
  std::unordered_map<std::string, std::shared_ptr<Function>> functions = {
    { "root", std::make_shared<Root>() },
    { "log", std::make_shared<Logarithm>() }
  };
  std::unordered_map<std::string, OperatorRule> operators = {
    // v-- Operator       v-- Order of operation  v-- Corresponding class
    { "+", { true, 0, std::make_shared<Addition>() } },
    { "-", { true, 0, std::make_shared<Subtraction>() } },
    { "*", { false, 1, std::make_shared<Multiplication>() } },
    { "/", { false, 1, std::make_shared<Division>() } },
    { "%", { false, 1, std::make_shared<Modulo>() } },
    { "^", { false, 2, std::make_shared<Exponentiation>() } },
  };
  std::unordered_map<std::string, double> constants
  {
    { std::make_pair("e",   2.718281828459045235) },
    { std::make_pair("pi",  3.141592653589793238) }
  };
  bool isConstant(const std::string& input);
};

