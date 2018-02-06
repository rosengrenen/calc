#include <complex>
#include <iostream>
#include <vector>

#include <string>
#include <algorithm>
#include <utility>

#include "Calculator.h"

int main(int argc, char **argv)
{
  Calculator c;
  std::string input;
  bool running = true;
  double result;
  while (running)
  {
    std::cout << "> ";
    std::getline(std::cin, input);
    result = c.evaluate(input);
    std::cout << result << std::endl;
  }
  return 0;
}
