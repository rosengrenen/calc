#include <complex>
#include <iostream>
#include <vector>

#include "Calculator.h"

int main(int argc, char **argv)
{
  Calculator c;
  double result = c.calculate("4-(-3)ABCansepi+7pi^13%8.15(7-(7^6))");
  std::cout << result << std::endl;
  std::cin.get();
  return 0;
}
