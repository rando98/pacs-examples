#include "newton.hpp"
#include <iostream>

#include "GetPot"

int
main(int argc, char **argv)
{
  std::function <double (double)> fun = [](double x) {return x*x*x + 5*x + 3;};
  std::function <double (double)> dfun = [](double x) {return 3*x*x + 5;};

  GetPot parser(argc, argv);

  std::size_t n_max = parser("n_max", 1000);
  double tol = parser("tol", 1e-6);
  double x0 = parser("x0", 0.0);

  std::cout << n_max << '\n';

  newton_solver solver(fun, dfun, n_max, tol);

  auto [x, iter] = solver.solve(x0); // structured binding

  std::cout << "Solution = " << x << std::endl;
  std::cout << "Iterations = " << iter << std::endl;

  return 0;
}
