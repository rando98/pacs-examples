#ifndef NEWTON_HPP
#define NEWTON_HPP

#include "NewtonMethodsSupport.hpp"
#include "JacobianFactory.hpp"

#include <iostream>

template<ProblemType Type>
class Newton
{
public:

  using T = NewtonTraits<Type>;

  Newton(const typename T::NonLinearSystemType& system_, std::unique_ptr<JacobianBase<Type>> jac_, NewtonOptions options_ = NewtonOptions())
    : system(system_), jac(std::move(jac_)), options(options_)
  {}

  Newton(const Newton&) = delete;

  NewtonResult<Type>
  solve(const typename T::VariableType& x0);

private:
  typename T::NonLinearSystemType system;
  std::unique_ptr<JacobianBase<Type>> jac; // not copy constructable => class Newton not copy consryctable
  NewtonOptions options;
  NewtonResult<Type> result;
};

// ------------------------------------------------------------------------
// DEFINITION OF METHODS

template<ProblemType Type>
NewtonResult<Type>
Newton<Type>::solve(const typename T::VariableType &x0)
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

      norm_res = T::compute_norm(res);
      norm_incr = T::compute_norm(delta);

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


#endif /* NEWTON_HPP_ */
