#include "newton.hpp"

newton_solver::newton_solver( std::function<double (double)> f,
                              std::function<double (double)> df,
                              unsigned int n_max, double tol)
                              : fun(f), fun_prime(df), n_max_iter(n_max), tolerance(tol)
{}

std::pair<double, std::size_t>
newton_solver::solve(double x0)
{
  double x = x0;
  std::size_t iter;

  for (iter = 0; iter < n_max_iter; ++iter)
  {
    double dx = -fun(x)/fun_prime(x);

    x += dx;

    if (std::abs(dx) < tolerance) // stopping criterion based on increments (my choice what criterion to use)
      break;
  }

  return std::make_pair(x, iter);
}
