#include "Calculator.h"

#include <algorithm>

#include "operands/Constant.h"
#include "operands/Expression.h"
#include "operands/FunctionCall.h"

double Calculator::evaluate(const std::string& input)
{
  this->expression = nullptr;
  auto parts = this->split(input);
  this->validate(parts);
  if (parts.size() > 1)
  {
    if (auto itr = this->variables.find(parts.at(0)); itr != this->variables.end() && parts.at(1) == "=")
    {
      if (itr->second.first)
      {
        this->parse({ parts.begin() + 2, parts.end() }, this->expression);
        return itr->second.second = this->expression->calc();
      }
    }
  }
  this->parse(parts, this->expression);
  return this->variables.find("ans")->second.second = this->expression->calc();
}

void Calculator::parse(std::vector<std::string> parts, std::unique_ptr<Operand>& term)
{
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
    if (auto itr = this->variables.find(parts.at(0)); itr != this->variables.end())
    {
      term = std::make_unique<Constant>(itr->second.second);
      return;
    }
    if (auto itr = this->constants.find(parts.at(0)); itr != this->constants.end())
    {
      term = std::make_unique<Constant>(itr->second);
      return;
    }
    term = std::make_unique<Constant>(std::stod(parts.at(0)));
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
  for (auto& itr : this->operators)
  {
    delimiters.push_back(itr.first);
  }
  for (auto& function : this->functions)
  {
    delimiters.push_back(function.first);
  }
  for (auto& constant : this->constants)
  {
    delimiters.push_back(constant.first);
  }
  for (auto& variable : this->variables)
  {
    delimiters.push_back(variable.first);
  }
  for (auto& bracket : this->brackets)
  {
    delimiters.push_back(bracket.second.first);
    delimiters.push_back(bracket.second.second);
  }
  for (auto& miscSplitter : this->miscSplitters)
  {
    delimiters.push_back(miscSplitter);
  }
  for (auto itr = input.begin(); itr != input.end();)
  {
    if (*itr == ' ')
    {
      itr++;
      continue;
    }
    bool found = false;
    for (auto & delimiter : delimiters)
    {
      auto a = input.find(delimiter, itr - input.begin());
      if (a == itr - input.begin())
      {
        found = true;
        itr += delimiter.size();
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
                    parts.empty())
                {
                  unaryFound = true;
                  if (chunk.empty())
                  {
                    parts.back() += delimiter;
                    break;
                  }
                  else
                  {
                    parts.back() += chunk;
                    parts.push_back(delimiter);
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
        parts.push_back(delimiter);
        break;
      }
    }
    if (!found)
    {
      chunk += *itr;
      itr++;
    }
  }
  if (!chunk.empty())
  {
    parts.push_back(chunk);
  }
  // Add *'s
  if (parts.size() > 1)
  {
    auto itr = parts.begin();
    while (itr != parts.end())
    {
      if (itr + 1 == parts.end())
      {
        break;
      }
      // ") (" and later on "} {"
      if (!(this->isCloseBracket(*itr) && this->isOpenBracket(*(itr + 1))))
      {
        if (!((this->isConstant(*itr) || this->isVariable(*itr)) && this->isOpenBracket(*(itr + 1))))
        {
          // "5 (" or "pi (" or "A ("
          // ") pi" or ") root" or ") ans"
          if (!(this->isCloseBracket(*itr) && (this->isConstant(*(itr + 1)) || this->isFunction(*(itr + 1)) || this->isVariable(*(itr + 1)))))
          {
            // "5 5"    "5 A"     "5 log" 
            // "pi e"   "pi C"    "pi root" 
            // "ans pi" "ans ans" "ans log"
            if (!((this->isConstant(*itr) || this->isVariable(*itr)) && (this->isConstant(*(itr + 1)) || this->isVariable(*(itr + 1)) || this->isFunction(*(itr + 1)))))
            {
              itr++;
              continue;
            }
          }
        }
      }
      auto offset = itr - parts.begin();
      parts.insert(itr + 1, "*");
      itr = parts.begin() + offset + 1;
    }
  }
  return parts;
}

#include <stack>

void Calculator::validate(const std::vector<std::string>& parts)
{
  std::stack<int> opening;
  std::stack<int> closing;
  for (auto& part : parts)
  {
    if (this->isOpenBracket(part))
    {
      for (auto& bracket : this->brackets)
      {
        if (bracket.second.first == part)
        {
          opening.push(bracket.first);
          continue;
        }
      }
    }
    else if (this->isCloseBracket(part))
    {
      for (auto& bracket : this->brackets)
      {
        if (bracket.second.second == part)
        {
          if (opening.top() == bracket.first)
          {
            opening.pop();
          }
          else
          {
            closing.push(bracket.first);
          }
          continue;
        }
      }
    }
  }
}

bool Calculator::isConstant(const std::string& input)
{
  if (this->constants.find(input) != this->constants.end())
  {
    return true;
  }
  try
  {
    std::stod(input);
    return true;
  }
  catch (std::invalid_argument)
  {

  }
  return false;
}

bool Calculator::isFunction(const std::string& input)
{
  return this->functions.find(input) != this->functions.end();
}

bool Calculator::isOperator(const std::string& input)
{
  return this->operators.find(input) != this->operators.end();
}

bool Calculator::isVariable(const std::string& input)
{
  return this->variables.find(input) != this->variables.end();
}

bool Calculator::isBracket(const std::string& input)
{
  for (auto& bracket : this->brackets)
  {
    if (input == bracket.second.first || input == bracket.second.second)
      return true;
  }
  return false;
}

bool Calculator::isOpenBracket(const std::string& input)
{
  for (auto& bracket : this->brackets)
  {
    if (input == bracket.second.first)
    {
      return true;
    }
  }
  return false;
}

bool Calculator::isCloseBracket(const std::string& input)
{
  for (auto& bracket : this->brackets)
  {
    if (input == bracket.second.second)
    {
      return true;
    }
  }
  return false;
}
