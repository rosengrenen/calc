#include "Calculator.h"

#include <algorithm>
#include <iostream>
#include <stack>

void Calculator::calculate(const std::string& input)
{
  this->parse(input);
  // this->evalutate("Whatever is returned by parse");
}

//class Value
//{
//public:
//  virtual double calc() = 0;
//};
//
//class Term
//{
//public:
//
//  double calc()
//  {
//    return this->opr->calc(left->calc(), right->calc());
//  }
//private:
//  std::unique_ptr<Term> left;
//  std::unique_ptr<Term> right;
//  std::unique_ptr<Operator> opr;
//};
//
//class Expression
//{
//public:
//  // Operators?
//private:
//  std::vector<Term> expr;
//};

double Calculator::parse(std::string input)
{
  // Split
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
  // Validate!
  // Add asterixes between constant/parentheses and parentheses where no operator is present
  // Remove empty spaces
  /* for (std::string::size_type i = 0; (i = input.find(" ", i)) != std::string::npos;)
{
  input.replace(i, 1, "");
}*/
// Variables (ans)
// Split the string *, /, %, +, -, (, )
// 1. Functions
// 2. Parentheses
// 3. ^
// 4. * / %
// 5. + -
// Note: unary plus and minus have to be taken care of
  std::cout << "Durr.." << std::endl;
  auto itr = input.begin();
  int parenthesesLevel = 0;
  // Make own, this is already used before
  int operatorLevel = 0;
  // Make flag check for operator level available?
  std::vector<std::pair<std::vector<std::string>::iterator, std::string>> offsets;
  size_t offset = 0;
  while (true)
  {
    offsets.resize(0);
    for (auto& opr : this->operators)
    {
      if (opr.second.first == operatorLevel)
      {
        offsets.push_back(std::make_pair(std::find(parts.begin() + offset, parts.end(), opr.first), opr.first));
        //if (itr == input.end())
        //{
        //  // Nothing more to find, increase the operator level
        //}
        //else
        //{

        //}
      }
    }
    if (offsets.empty())
    {
      break;
    }
    else
    {
      int min = parts.size();
      for (auto offset : offsets)
      {
        if (parts.begin() - offset.first < min)
        {
          min = parts.begin() - offset.first;
        }
      }
      // Now we know which one to wrap
    }
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
  return 0.0;
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
