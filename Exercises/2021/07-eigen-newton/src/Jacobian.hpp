#ifndef JACOBIAN_HPP
#define JACOBIAN_HPP

#include <iostream>
#include "NewtonTraits.hpp"

template<ProblemType Type>
class JacobianBase
{
public:
  using T = NewtonTraits<Type>;

  JacobianBase() = default;
  // J(x)*delta_x = res

  virtual
  typename T::VariableType
  solve(const typename T::VariableType& x, const typename T::VariableType& res) const = 0;

  virtual ~JacobianBase() = default;

};

template<ProblemType Type>
class DiscreteJacobian: public JacobianBase<Type>
{
public:
  using T = NewtonTraits<Type>;
  DiscreteJacobian(const typename T::NonLinearSystemType& system_, const double& h_)
    : system(system_), h(h_)
  {};

  virtual
  typename T::VariableType
  solve(const typename T::VariableType& x, const typename T::VariableType& res) const override;

private:
  typename T::NonLinearSystemType system;
  double h;
};

template<ProblemType Type>
class FullJacobian: public JacobianBase<Type>
{
public:
  using T = NewtonTraits<Type>;
  FullJacobian(const typename T::JacobianFunctionType& jac_)
    : jac(jac_)
  {}

  virtual
  typename T::VariableType
  solve(const typename T::VariableType& x, const typename T::VariableType& res) const override;

private:
  typename T::JacobianFunctionType jac;

};

// ------------------------------------------------------------------------------
// DEFINITION OF METHODS

template<ProblemType Type>
typename NewtonTraits<Type>::VariableType
DiscreteJacobian<Type>::solve(const typename T::VariableType& x, const typename T::VariableType& res) const
{
  // J_i \approx(f(x+h)-f(x-h)) /(2*h)
  const size_t n = x.size();

  typename T::JacobianMatrixType J(n, n);

  for(size_t i=0; i<n; i++)
  {
    typename T::VariableType x_m(x); //x_minus
    typename T::VariableType x_p(x); //x_plus

    x_m[i] -= h;
    x_p[i] += h;

    typename T::VariableType f_m{system(x_m)};
    typename T::VariableType f_p{system(f_p)};

    J.col(i) = (f_m - f_p) / (2*h);
  }

  return J.fullPivLu().solve(res);
}

template<> // Specialization
typename NewtonTraits<ProblemType::Scalar>::VariableType
DiscreteJacobian<ProblemType::Scalar>::solve(const typename T::VariableType& x, const typename T::VariableType& res) const
{

  typename T::VariableType x_m(x); //x_minus
  typename T::VariableType x_p(x); //x_plus

  x_m -= h;
  x_p += h;

  typename T::VariableType f_m{system(x_m)};
  typename T::VariableType f_p{system(f_p)};

  typename T::JacobianMatrixType J = (f_p - f_m)/(2*h);

  return res / J;
}
// In case we will have to add a new ProblemType (e.g ProblemType::mixed, for instance) I will have to add a new
// Specialization.

template<ProblemType Type>
typename NewtonTraits<Type>::VariableType
FullJacobian<Type>::solve(const typename T::VariableType& x, const typename T::VariableType& res) const
{
  //jac(x) \ b
  const typename T::JacobianMatrixType J = jac(x);

  return J.fullPivLu().solve(res);
}

template<>
typename NewtonTraits<ProblemType::Scalar>::VariableType
FullJacobian<ProblemType::Scalar>::solve(const typename T::VariableType& x, const typename T::VariableType& res) const
{
  //jac(x) * delta = b ---> delta = b/Jac(x) : In the scalar case Jac is nothing but the derivative of the function

  return res/jac(x);
}

#endif /* JACOBIAN_HPP */
