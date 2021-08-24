#include "Newton.hpp"

#include <iostream>
#include <limits>

NewtonResult
Newton::solve(const T::VariableType &x0)
{
  // C++17 structured binding.
  // Get all options and result.
  const auto &[tol_res, tol_incr, max_iter] = this->options;

  auto &[solution, norm_res, norm_incr, iteration, converged] =
    this->result;

  // The initial step is to compute the relevant quantities
  // from the initial conditions.
  solution  = x0;
  iteration = 0;

  // Initial values for tests of convergence and stagnation.
  converged  = false;

  for (iteration = 0; iteration < max_iter; ++iteration)
    {
      // x^[k+1] = x^[k] - (Jf)(x^[k])^-1 * f(x^[k])   NEWTON METHOD
      // res := f(x^[k])
      // J := (Jf)(x^[k])^-1
      // delta := (Jf)(x^[k])^-1 * f(x^[k])

      // => J^-1 * res = delta =>
      // J*delta = res
      // x = x - delta
      auto res = system(solution);

      // Compute the increment
      auto delta = jac->solve(solution, res);

      solution -= delta;

      norm_res = res.norm();
      norm_incr = delta.norm();

      // Test convergence.
      converged = ((norm_res <= tol_res) && (norm_incr <= tol_incr));

      std::cout << "  Iteration " << iteration;
      std::cout << ", residual: " << norm_res;
      std::cout << ", increment: " << norm_incr;
      std::cout << std::endl;

      if (converged)
        break;
    }

  return result;
}
