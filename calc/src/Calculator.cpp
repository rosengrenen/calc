#include "Calculator.h"

#include <algorithm>

#include "operands/Constant.h"
#include "operands/Expression.h"
#include "operands/FunctionCall.h"

double Calculator::assign(const std::vector<std::string>& parts)
{

}

double Calculator::calculate(const std::vector<std::string>& parts)
{
  this->parse(parts, this->expression);
  return this->expression->calc();
}

double Calculator::evaluate(const std::string & input)
{
  this->expression = nullptr;
  auto split = this->split(input);
  return this->calculate(split);
}

void Calculator::parse(std::vector<std::string> parts, std::unique_ptr<Operand>& term)
{
  //TODO: assign to variable
  // Remove unnecessary parentheses
  while (parts.at(0) == "(" && parts.at(parts.size() - 1) == ")")
  {
    parts.erase(parts.begin());
    parts.erase(parts.end() - 1);
  }
  if (parts.empty())
  {
    throw 0;
  }
  else if (parts.size() == 1)
  {
    // Find the variable
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

std::vector<std::string> Calculator::split(const std::string& input)
{
  std::string chunk;
  std::vector<std::string> parts;
  std::vector<std::string> delimiters;
  for (auto itr = this->operators.begin(); itr != this->operators.end(); ++itr)
  {
    delimiters.push_back(itr->first);
  }
  for (auto itr = this->functions.begin(); itr != this->functions.end(); ++itr)
  {
    delimiters.push_back(itr->first);
  }
  for (auto itr = this->constants.begin(); itr != this->constants.end(); ++itr)
  {
    delimiters.push_back(itr->first);
  }
  for (auto itr = this->variables.begin(); itr != this->variables.end(); ++itr)
  {
    delimiters.push_back(itr->first);
  }
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
        bool unaryFound = false;
        if (!parts.empty())
        {
          for (auto& opr : this->operators)
          {
            if (parts.back() == opr.first)
            {
              if (opr.second.unary)
              {
                if ((parts.size() > 1 && *(parts.end() - 2) == "(") ||
                  (parts.size() == 0))
                {
                  unaryFound = true;
                  if (chunk.empty())
                  {
                    parts.back() += *it;
                    break;
                  }
                  else
                  {
                    parts.back() += chunk;
                    parts.push_back(*it);
                    chunk.clear();
                    break;
                  }
                }
              }
            }
          }
        }
        if (unaryFound)
        {
          break;
        }
        if (!chunk.empty())
        {
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
