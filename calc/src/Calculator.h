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
#include "operations/Assignment.h"
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
  double evaluate(const std::string& input);
private:
  std::unique_ptr<Operand> expression;
  std::unordered_map<std::string, std::shared_ptr<Function>> functions = {
    { "root",   std::make_shared<Root>()      },
    { "log",    std::make_shared<Logarithm>() },
  };
  std::unordered_map<std::string, OperatorRule> operators {
    { "+", { false, 0, std::make_shared<Addition>()       } },
    { "-", { true,  0, std::make_shared<Subtraction>()    } },
    { "*", { false, 1, std::make_shared<Multiplication>() } },
    { "/", { false, 1, std::make_shared<Division>()       } },
    { "%", { false, 1, std::make_shared<Modulo>()         } },
    { "^", { false, 2, std::make_shared<Exponentiation>() } },
    { "=", { false, 3, std::make_shared<Assignment>()     } },
  };
  std::unordered_map<std::string, double> constants {
    { std::make_pair("e",   2.718281828459045235) },
    { std::make_pair("pi",  3.141592653589793238) },
  };
  std::unordered_map<std::string, std::pair<bool, double>> variables {
    { "ans",  std::make_pair(false, 0.0) },
    { "A",    std::make_pair(true,  0.0) },
    { "B",    std::make_pair(true,  0.0) },
    { "C",    std::make_pair(true,  0.0) },
    { "D",    std::make_pair(true,  0.0) },
    { "E",    std::make_pair(true,  0.0) },
    { "F",    std::make_pair(true,  0.0) },
    { "G",    std::make_pair(true,  0.0) },
    { "H",    std::make_pair(true,  0.0) },
    { "I",    std::make_pair(true,  0.0) },
    { "J",    std::make_pair(true,  0.0) },
    { "K",    std::make_pair(true,  0.0) },
    { "L",    std::make_pair(true,  0.0) },
    { "M",    std::make_pair(true,  0.0) },
    { "N",    std::make_pair(true,  0.0) },
    { "O",    std::make_pair(true,  0.0) },
    { "P",    std::make_pair(true,  0.0) },
    { "Q",    std::make_pair(true,  0.0) },
    { "R",    std::make_pair(true,  0.0) },
    { "S",    std::make_pair(true,  0.0) },
    { "T",    std::make_pair(true,  0.0) },
    { "U",    std::make_pair(true,  0.0) },
    { "V",    std::make_pair(true,  0.0) },
    { "W",    std::make_pair(true,  0.0) },
    { "X",    std::make_pair(true,  0.0) },
    { "Y",    std::make_pair(true,  0.0) },
    { "Z",    std::make_pair(true,  0.0) },
  };
  std::unordered_map<int, std::pair<std::string, std::string>> brackets {
    { 0, std::make_pair("(", ")") },
    { 1, std::make_pair("{", "}") },
    { 2, std::make_pair("[", "]") },
  };
  std::vector<std::string> miscSplitters { 
    "=", 
    ",", 
  };
  void parse(std::vector<std::string> parts, std::unique_ptr<Operand>& term);
  std::vector<std::string> split(const std::string& input);
  void validateBrackets(std::vector<std::string>& parts);
  void addAsterisks(std::vector<std::string>& parts);
  void trimBrackets(std::vector<std::string>& parts);
  void parseValue(const std::vector<std::string>& parts, std::unique_ptr<Operand>& term);
  void parseOperator(const std::vector<std::string>& parts, std::unique_ptr<Operand>& term);
  void parseFunction(const std::vector<std::string>& parts, std::unique_ptr<Operand>& term);
  bool isConstant(const std::string& input);
  bool isVariable(const std::string& input);
  bool isFunction(const std::string& input);
  bool isOperator(const std::string& input);
  bool isBracket(const std::string& input);
  bool isOpeningBracket(const std::string& input);
  bool isClosingBracket(const std::string& input);
};

