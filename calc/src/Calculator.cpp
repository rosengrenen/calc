#include "Calculator.h"

#include <algorithm>
#include <iostream>
#include <stack>

#include "operands/Constant.h"
#include "operands/Expression.h"
#include "operands/FunctionCall.h"

double Calculator::calculate(std::string input)
{
  //TODO: Validate!
  auto split = this->split(input);
  //TODO: Add asterixes between constant/parentheses and parentheses where no operator is present
  this->parse(split, this->expression);
  return this->expression->calc();
}

void Calculator::parse(std::vector<std::string> parts, std::unique_ptr<Operand>& term)
{
  //TODO: variables and "ans"
  //TODO: unary plus and minus
  if (parts.empty())
  {
    throw 0;
  }
  else if (parts.size() == 1)
  {
    auto itr = this->constants.find(parts.at(0));
    if (itr != this->constants.end())
    {
      term = std::make_unique<Constant>(itr->second);
    }
    else
    {
      term = std::make_unique<Constant>(std::stod(parts.at(0)));
    }
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
      if (opr.second.order == operatorLevel)
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
            Expression *e = dynamic_cast<Expression *>(term.get());
            this->parse(std::vector<std::string>{ parts.begin(), itr }, e->left);
            e->opr = this->operators.find(*itr)->second.opr;
            this->parse(std::vector<std::string>{ itr + 1, parts.end() }, e->right);
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
  // Find a function
  for (auto itr = parts.begin(); itr != parts.end(); ++itr)
  {
    // Iterate until we find a function
    if (this->functions.find(*itr) != functions.end())
    {
      term = std::make_unique<FunctionCall>();
      FunctionCall *f = dynamic_cast<FunctionCall *>(term.get());
      f->func = this->functions.find(*itr)->second;
      // Skip func name in iteration
      itr++;
      // Find that the parentheses level is 1, inside the function call parentheses, but not further
      int parentheses = 0;
      auto offset = itr + 1; // Skip func name and parentheses
      for (auto i = itr; i != parts.end(); ++i)
      {
        if (*i == "(")
        {
          parentheses++;
        }
        else if (*i == ")")
        {
          parentheses--;
        }
        if (parentheses < 1)
        {
          // We've exited the function call parentheses, add from offset til end in the argument vector
          if (offset != i)
          {
            f->args.push_back(nullptr);
            this->parse({ offset, i }, f->args.back());
          }
          break;
        }
        if (parentheses == 1 && *i == ",")
        {
          f->args.push_back(nullptr);
          this->parse({ offset, i }, f->args.back());
          offset = i + 1;
        }
      }
    }
  }
}

std::vector<std::string> Calculator::split(std::string input)
{
  std::vector<std::string> delimiters = {
    "^",
    "*",
    "/",
    "%",
    "+",
    "-",
    "(",
    ")",
    "A",
    "B",
    "C",
    "D",
    "E",
    "F",
    "G",
    "H",
    "I",
    "J",
    "K",
    "L",
    "M",
    "N",
    "O",
    "P",
    "Q",
    "R",
    "S",
    "T",
    "U",
    "V",
    "W",
    "X",
    "Y",
    "Z",
    "ans"
  };
  for (auto itr = this->constants.begin(); itr != this->constants.end(); ++itr)
  {
    delimiters.push_back(itr->first);
  }
  std::string chunk;
  std::vector<std::string> parts;
  for (auto itr = input.begin(); itr != input.end();)
  {
    if (*itr == ' ')
    {
      continue;
    }
    bool found = false;
    for (auto it = delimiters.begin(); it != delimiters.end(); ++it)
    {
      auto a = input.find(*it, itr - input.begin());
      if (a == itr - input.begin())
      {
        found = true;
        itr += it->size();
        if (!chunk.empty())
        {
          //auto i = this->operators.find(chunk);
          //if (i != this->operators.end())
          //{
          //  if (i->second.unary)
          //  {
          //    // (-5)
          //    // -5
          //    if (!parts.empty())
          //    {
          //      if (parts.back() == " ")
          //      {

          //      }
          //    }
          //  }
          //}
          parts.push_back(chunk);
          chunk.clear();
        }
        parts.push_back(*it);
        break;
      }
    }
    if (!found)
    {
      chunk += *itr;
      itr++;
    }
  }
  // Add *'s
  if (parts.size() > 1)
  {
    auto itr = parts.begin();
    while (itr != parts.end())
    {
      if (itr + 1 != parts.end())
      {
        if ((*itr == ")" && *(itr + 1) == "(") ||
            (this->isConstant(*itr) && *(itr + 1) == "(") ||
            (*itr == ")" && this->isConstant(*(itr + 1))) ||
            (this->isConstant(*itr) && this->isConstant(*(itr + 1))))
        {
          auto offset = itr - parts.begin();
          parts.insert(itr + 1, "*");
          itr = parts.begin() + offset + 1;
        }
        else
        {
          itr++;
        }
      }
      else
      {
        break;
      }
    }
  }
  return parts;
}

bool Calculator::isConstant(const std::string& input)
{
  return (this->operators.find(input) == this->operators.end() &&
          input != "(" && input != ")");
}
