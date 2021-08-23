#include "Jacobian.hpp"


NewtonTraits::VariableType
DiscreteJacobian::solve(const T::VariableType& x, const T::VariableType& res) const
{
  // J_i \approx(f(x+h)-f(x-h)) /(2*h)
  const size_t n = x.size();

  T::JacobianMatrixType J(n, n);

  for(size_t i=0; i<n; i++)
  {
    T::VariableType x_m(x); //x_minus
    T::VariableType x_p(x); //x_plus

    x_m[i] -= h;
    x_p[i] += h;

    T::VariableType f_m{system(x_m)};
    T::VariableType f_p{system(f_p)};

    J.col(i) = (f_m - f_p) / (2*h);
  }

  return J.fullPivLu().solve(res);
}

NewtonTraits::VariableType
FullJacobian::solve(const T::VariableType& x, const T::VariableType& res) const
{
  //jac(x) \ b
  const T::JacobianMatrixType J = jac(x);

  return J.fullPivLu().solve(res);
}
