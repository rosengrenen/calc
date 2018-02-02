#include <complex>
#include <iostream>

#include "Calculator.h"

int main(int argc, char **argv)
{
  Calculator c;
  c.calculate("5(5 +  4)10*4/3+7*log(30)/log(30, 30)");
}
