#include "newton.hpp"
#include <iostream>

double
fun(double x)
{
  return x*x*x + 5*x + 3;
}

double
dfun(double x)
{
  return 3*x*x + 5;
}

int
main(int argc, char **argv)
{
  newton_solver solver(fun, dfun, 1000, 1e-6);

  auto [x, iter] = solver.solve(0.0); // structured binding

  std::cout << "Solution = " << x << std::endl;
  std::cout << "Iterations = " << iter << std::endl;

  return 0;
}
