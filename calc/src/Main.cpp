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
  std::string i("4-(-3)ABCansepi+7pi^13%8.15(7-(7^6))");
  double result = c.calculate(i);
  std::cout << result << std::endl;
  std::cin.get();
  return 0;
}
