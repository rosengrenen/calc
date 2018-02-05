#include "Calculator.h"

#include <algorithm>
#include <iostream>
#include <stack>

#include "operands/Constant.h"
#include "operands/Expression.h"
#include "operands/FunctionCall.h"

double Calculator::calculate(const std::string& input)
{
  // Validate!
  auto split = this->split(input);
  // Add asterixes between constant/parentheses and parentheses where no operator is present
  this->parse(split, this->expression);
  std::cout << this->expression->print();
  //return this->expr.evaluate();
  return 0.0;
}

void Calculator::parse(std::vector<std::string> parts, std::unique_ptr<Operand>& term)
{
  // Variables (ans)
  // Note: unary plus and minus have to be taken care of
  if (parts.empty())
  {
    throw 0;
  }
  else if (parts.size() == 1)
  {
    term = std::make_unique<Constant>(std::stod(parts.at(0)));
    return;
  }
  // Remove unnecessary parentheses
  while (parts.at(0) == "(" && parts.at(parts.size() - 1) == ")")
  {
    parts.erase(parts.begin());
    parts.erase(parts.end() - 1);
  }
  int operatorLevel = 0;
  auto itr = parts.begin();
  while (true)
  {
    bool done = true;
    if (itr == parts.end())
    {
      operatorLevel++;
      itr = parts.begin();
    }
    for (auto& opr : this->operators)
    {
      if (opr.second.first == operatorLevel)
      {
        done = false;
        if (opr.first == *itr)
        {
          // The current part is a fitting operator
          // Make sure it is at base level (not in nested parentheses)
          int parentheses = 0;
          for (auto i = parts.begin(); i < itr; ++i)
          {
            if (*i == "(")
            {
              parentheses++;
            }
            else if (*i == ")")
            {
              parentheses--;
            }
          }
          if (parentheses == 0)
          {
            term = std::make_unique<Expression>();
            this->parse(std::vector<std::string>{ parts.begin(), itr }, term->left);

            term->opr = this->operators.find(*itr)->second.second;
            this->parse(std::vector<std::string>{ itr + 1, parts.end() }, term->right);
            return;
          }
          continue;
        }
      }
    }
    if (done)
    {
      break;
    }
    itr++;
  }
  //std::vector<Expression> expression;
  //std::stack<std::vector<Expression> *> current;
  //current.push(&expression);
  //for (int i = 0; i < parts.size(); ++i)
  //{
  //  // Find functions first tho
  //  if (parts.at(i) == "(")
  //  {
  //    Expression e;
  //    e.type = Expression::NOT_SINGLE;;
  //    current.top()->push_back(e);
  //    current.push(&current.top()->back().notSingle);
  //  }
  //  else if (parts.at(i) == ")")
  //  {
  //    current.pop();
  //  }
  //  else
  //  {
  //    Expression e;
  //    e.type = Expression::SINGLE;
  //    e.single = parts.at(i);
  //    current.top()->push_back(e);
  //  }
  //}
  //std::stack<std::vector<Expression> *> stack;
  //stack.push(&expression);
  //std::stack<int> i;
  //i.push(0);
  //while (!stack.empty())
  //{
  //  if (i.top() >= stack.top()->size())
  //  {
  //    i.pop();
  //    stack.pop();
  //  }
  //  else if (stack.top()->at(i.top()).type == Expression::SINGLE)
  //  {
  //    for (int prints = 0; prints < stack.size() - 1; ++prints)
  //    {
  //      std::cout << "\t";
  //    }
  //    std::cout << stack.top()->at(i.top()).single << std::endl;
  //    i.top()++;
  //  }
  //  else if (stack.top()->at(i.top()).type == Expression::NOT_SINGLE)
  //  {
  //    stack.push(&stack.top()->at(i.top()).notSingle);
  //    i.top()++;
  //    i.push(0);
  //  }
  //}
  int a = 0;




  /*struct StrLvl
  {
    int level;
    std::string part;
  };
  int level = 0;
  int aLevel = 0;
  std::vector<std::vector<StrLvl>> expressions(1);
  for (int i = 0; i < parts.size(); ++i)
  {
    if (parts.at(i) == "(")
    {
      level++;
      if (expressions.size() < level + 1)
      {
        expressions.resize(level + 1);
      }
      expressions.at(level).push_back({ aLevel, "(" });
      aLevel++;
      level++;
      if (expressions.size() < level + 1)
      {
        expressions.resize(level + 1);
      }
    }
    else if (parts.at(i) == ")")
    {
      level++;
      if (expressions.size() < level + 1)
      {
        expressions.resize(level + 1);
      }
      aLevel--;
      expressions.at(level).push_back({ aLevel, ")" });
      level++;
      if (expressions.size() < level + 1)
      {
        expressions.resize(level + 1);
      }
    }
    else
    {
      expressions.at(level).push_back({ aLevel, parts.at(i) });
    }
  }
  std::cout << "\n\n";
  for (auto& expression : expressions)
  {
    if (!expression.empty())
      for (int i = 0; i < expression.at(0).level; ++i)
      {
        std::cout << "\t";
      }
    for (auto& part : expression)
    {

      std::cout << part.part << " ";
    }
    std::cout << std::endl;
  }*/
  //for (int i = 0; i < parts.size(); ++i)
  //{
  //  const auto& f = this->functions.find(parts.at(i));
  //  if (f != this->functions.end())
  //  {
  //    // Function found
  //    // Foreach argument passed, add it as a parameter and then calc
  //  }
  //}

  //for (int i = 0; i < parts.size(); ++i)
  //{
  //  if (parts.at(i) == "*")
  //  {
  //    // This would work for 5*5 but not (5)*(5+4)
  //    if (this->isNumber(parts.at(i - 1)) && this->isNumber(parts.at(i + 1)))
  //    {

  //    }
  //  }
  //  else if (parts.at(i) == "/")
  //  {

  //  }
  //  else if (parts.at(i) == "%")
  //  {

  //  }
  //}
  // Look for operators in order of operations (* % /) -> (+ -)
}

bool Calculator::isNumber(const std::string& input)
{
  return true;
}

//std::vector<std::string> Calculator::split(const std::string & input)
//{
//  std::string delimiters = "*/%+-()^,"; // []
//  std::string chunk;
//  std::vector<std::string> parts;
//  bool flag;
//  for (auto& part : input)
//  {
//    if (part == ' ')
//    {
//      continue;
//    }
//    flag = false;
//    for (auto& delimiter : delimiters)
//    {
//      if (part == delimiter)
//      {
//        flag = true;
//        if (!chunk.empty())
//        {
//          parts.push_back(chunk);
//        }
//        parts.emplace_back(1, delimiter);
//        chunk = "";
//        break;
//      }
//    }
//    if (!flag)
//    {
//      chunk += part;
//    }
//  }
//  if (!chunk.empty())
//  {
//    parts.push_back(chunk);
//  }
//  return parts;
//}

bool Calculator::isOperator(const std::string& input)
{
  return false;// return (this->operators.find(input) != this->operators.end());
}

bool Calculator::isOperand(const std::string& input)
{
  return false;
}

std::vector<std::string> Calculator::split(const std::string& input)
{
  std::string delimiters = "*/%+-()^,"; // []
  std::string chunk;
  std::vector<std::string> parts;
  bool flag;
  for (auto& part : input)
  {
    if (part == ' ')
    {
      continue;
    }
    flag = false;
    for (auto& delimiter : delimiters)
    {
      if (part == delimiter)
      {
        flag = true;
        if (!chunk.empty())
        {
          parts.push_back(chunk);
        }
        parts.emplace_back(1, delimiter);
        chunk = "";
        break;
      }
    }
    if (!flag)
    {
      chunk += part;
    }
  }
  if (!chunk.empty())
  {
    parts.push_back(chunk);
  }
  return parts;
}
