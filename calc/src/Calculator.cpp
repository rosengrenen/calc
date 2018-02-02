#include "Calculator.h"

#include <iostream>
#include <vector>

void Calculator::calculate(const std::string& input)
{
  this->parse(input);
}

double Calculator::parse(const std::string& input)
{
  // Variables (ans)
  // Split the string *, /, %, +, -, (, )
  std::string delimiters = "*/%+-()^"; // []
  std::string chunk;
  std::vector<std::string> parts;
  for (auto& part : input)
  {
    bool flag = false;
    for (auto& delimiter : delimiters)
    {
      if (part == delimiter)
      {
        flag = true;
        parts.push_back(chunk);
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
  // Process stuffs
  for (auto& part : parts)
  {
    std::cout << part << std::endl;
  }
  for (int i = 0; i < parts.size(); ++i)
  {
    if (parts.at(i) == "*")
    {
      // This would work for 5*5 but not (5)*(5+4)
      if (this->isNumber(parts.at(i - 1)) && this->isNumber(parts.at(i + 1)))
      {

      }
    }
    else if (parts.at(i) == "/")
    {

    }
    else if (parts.at(i) == "%")
    {

    }
  }
  size_t offset;
  
  offset = input.find('('); // Must not be a function
  if (offset != std::string::npos)
  {
    this->parse(input.substr(offset));
  }
  // Look for operators in order of operations (* % /) -> (+ -)

}

bool Calculator::isNumber(const std::string& input)
{
  return true;
}
