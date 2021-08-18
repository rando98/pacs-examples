#include "newton.hpp"
#include <iostream>

#include "GetPot"

#include "muparser_fun.hpp"

int
main(int argc, char **argv)
{
  GetPot parser(argc, argv);

  std::size_t n_max = parser("n_max", 1000);
  double tol = parser("tol", 1e-6);
  double x0 = parser("x0", 0.0);

  std::string fun_expr = parser("fun", "x^3 + 5*x + 3");
  std::string dfun_expr = parser("dfun","3*x^2 + 5");

  muparser_fun fun(fun_expr);
  muparser_fun dfun(dfun_expr);

  newton_solver solver(fun, dfun, n_max, tol);

  auto [x, iter] = solver.solve(x0); // structured binding

  std::cout << "Solution = " << x << std::endl;
  std::cout << "Iterations = " << iter << std::endl;

  return 0;

}
