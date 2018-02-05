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
  double result = c.evaluate("5+5");
  std::cout << result << std::endl;
  std::cin.get();
  return 0;
}
