#include <complex>
#include <iostream>
#include <vector>

#include "Calculator.h"

int main(int argc, char **argv)
{
  Calculator c;
  double result = c.calculate("5*((5 +  4)*10)*4/3+7*(log(10)/log(30, 30))");
  std::cout << result << std::endl;
  std::cin.get();
  return 0;
}
