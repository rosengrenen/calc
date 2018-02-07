#include <complex>
#include <iostream>
#include <vector>

#include <string>
#include <algorithm>
#include <utility>

#include "Calculator.h"

#include "errors/UnmatchedBracketException.h"
#include "errors/InvalidInputException.h"

#include "operands/FunctionCall.h"

int main(int argc, char **argv)
{
  
  Calculator c;
  std::string input;
  while (true)
  {
    std::cout << "> ";
    std::getline(std::cin, input);
    try
    {
      std::cout << c.evaluate(input) << std::endl;
    }
    catch (const UnmatchedBracketException& e)
    {
      std::cout << e.what() << std::endl;
    }
    catch (const InvalidInputException& e)
    {
      std::cout << e.what() << std::endl;
    }
  }
  return 0;
}
