#include "Calculator.h"

#include <algorithm>
#include <stack>

#include "errors/InvalidInputException.h"
#include "errors/UnmatchedBracketException.h"

#include "operands/Constant.h"
#include "operands/Expression.h"
#include "operands/FunctionCall.h"

double Calculator::evaluate(const std::string& input)
{
  this->expression = nullptr;
  auto parts = this->split(input);
  this->validateBrackets(parts);
  this->addAsterisks(parts);
  this->parse(parts, this->expression);
  return this->variables.find("ans")->second.second = this->expression->calc();
}

void Calculator::parse(std::vector<std::string> parts, std::unique_ptr<Operand>& term)
{
  this->trimBrackets(parts);
  if (parts.empty())
  {
    throw InvalidInputException("Invalid input at ...");
  }
  else if (parts.size() == 1)
  {
    this->parseValue(parts, term);
  }
  else
  {
    this->parseOperator(parts, term);
    this->parseFunction(parts, term);
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
  return parts;
}

void Calculator::validateBrackets(std::vector<std::string>& parts)
{
  std::stack<int> opening;
  std::stack<int> closing;
  int length = 0;
  for (auto& part : parts)
  {
    length += part.size();
    if (this->isOpeningBracket(part))
    {
      for (auto& bracket : this->brackets)
      {
        if (bracket.second.first == part)
        {
          opening.push(bracket.first);
          break;
        }
      }
    }
    else if (this->isClosingBracket(part))
    {
      for (auto& bracket : this->brackets)
      {
        if (bracket.second.second == part)
        {
          if (!opening.empty())
          {
            if (opening.top() == bracket.first)
            {
              opening.pop();
              continue;
            }
            else
            {
              throw UnmatchedBracketException("Invalid closing bracket\"" + bracket.second.second + "\" at position " + std::to_string(length));
            }
          }
          closing.push(bracket.first);
          continue;
        }
      }
    }
  }
  if (!opening.empty())
  {
    while (!opening.empty())
    {
      parts.push_back(this->brackets.at(opening.top()).second);
      opening.pop();
    }
  }
  else if (!closing.empty())
  {
    size_t offset = 0;
    while (!closing.empty())
    {
      parts.insert(parts.begin() + offset, this->brackets.at(closing.top()).first);
      offset++;
      closing.pop();
    }
  }
}

void Calculator::addAsterisks(std::vector<std::string>& parts)
{ 
  if (parts.size() > 1)
  {
    auto itr = parts.begin();
    while (itr != parts.end())
    {
      if (itr + 1 == parts.end())
      {
        break;
      }
      if (!(this->isClosingBracket(*itr) && this->isOpeningBracket(*(itr + 1))))
      {
        if (!((this->isConstant(*itr) || this->isVariable(*itr)) && this->isOpeningBracket(*(itr + 1))))
        {
          if (!(this->isClosingBracket(*itr) && (this->isConstant(*(itr + 1)) || this->isFunction(*(itr + 1)) || this->isVariable(*(itr + 1)))))
          {
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
}

void Calculator::trimBrackets(std::vector<std::string>& parts)
{
  while (!parts.empty())
  {
    bool flag = true;
    for (auto& bracket : this->brackets)
    {
      if (parts.at(0) == bracket.second.first && parts.at(parts.size() - 1) == bracket.second.second)
      {
        flag = false;
        parts.erase(parts.begin());
        parts.erase(parts.end() - 1);
        break;
      }
    }
    if (flag)
    {
      break;
    }
  }
}

void Calculator::parseValue(const std::vector<std::string>& parts, std::unique_ptr<Operand>& term)
{ 
  if (auto itr = this->variables.find(parts.at(0)); itr != this->variables.end())
  {
    if (itr->second.first)
    {
      term = std::unique_ptr<Constant>(new Constant(itr->second.second, true));
    }
    else
    {
      term = std::make_unique<Constant>(itr->second.second);
    }
    return;
  }
  if (auto itr = this->constants.find(parts.at(0)); itr != this->constants.end())
  {
    term = std::make_unique<Constant>(itr->second);
    return;
  }
  term = std::make_unique<Constant>(std::stod(parts.at(0)));
}

void Calculator::parseOperator(const std::vector<std::string>& parts, std::unique_ptr<Operand>& term)
{ 
  bool flag = true;
  for (int oprLevel = 0; flag; ++oprLevel)
  {
    flag = false;
    for (auto itr = parts.begin(); itr != parts.end(); ++itr)
    {
      for (auto& opr : this->operators)
      {
        if (opr.second.order == oprLevel)
        {
          flag = true;
          if (opr.first == *itr)
          {
            int parentheses = 0;
            for (auto i = parts.begin(); i < itr; ++i)
            {
              if (this->isOpeningBracket(*i))
              {
                parentheses++;
              }
              else if (this->isClosingBracket(*i))
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

    }
  }
}

void Calculator::parseFunction(const std::vector<std::string>& parts, std::unique_ptr<Operand>& term)
{ 
  for (auto itr = parts.begin(); itr != parts.end(); ++itr)
  {
    if (this->isFunction(*itr))
    {
      term = std::make_unique<FunctionCall>();
      FunctionCall *f = dynamic_cast<FunctionCall *>(term.get());
      f->func = this->functions.find(*itr)->second;
      itr++;
      int parentheses = 0;
      auto offset = itr + 1;
      for (auto i = itr; i != parts.end(); ++i)
      {
        if (this->isOpeningBracket(*i))
        {
          parentheses++;
        }
        else if (this->isClosingBracket(*i))
        {
          parentheses--;
        }
        if (parentheses < 1)
        {
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

bool Calculator::isConstant(const std::string& input)
{
  if (this->constants.find(input) != this->constants.end())
  {
    return true;
  }
  bool sign = false;
  bool digit = false;
  bool period = false;
  for (auto& c : input)
  {
    if (c == '-')
    {
      if (sign || period)
      {
        return false;
      }
      sign = true;
    }
    else if (c == '.')
    {
      if (period)
      {
        return false;
      }
      period = true;
    }
    else if (char d = c - '0'; !(d < 0 || d > 9))
    {
      digit = true;
    }
    else
    {
      return false;
    }
  }
  return true;
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

bool Calculator::isOpeningBracket(const std::string& input)
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

bool Calculator::isClosingBracket(const std::string& input)
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
