#ifndef JACOBIAN_HPP
#define JACOBIAN_HPP

#include "NewtonTraits.hpp"

class JacobianBase
{
public:
  using T = NewtonTraits;

  JacobianBase() = default;

  // J(x)*delta_x = res
  virtual
  T::VariableType
  solve(const T::VariableType& x, const T::VariableType& res) const = 0;

  virtual ~JacobianBase() = default;

};

class DiscreteJacobian: public JacobianBase
{
public:
  DiscreteJacobian(const T::NonLinearSystemType& system_, const double& h_)
    : system(system_), h(h_)
  {}

  virtual
  T::VariableType
  solve(const T::VariableType& x, const T::VariableType& res) const override;

private:
  T::NonLinearSystemType system;
  double h;
};

class FullJacobian: public JacobianBase
{
public:
  FullJacobian(const T::JacobianFunctionType& jac_)
    : jac(jac_)
  {}

  virtual
  T::VariableType
  solve(const T::VariableType& x, const T::VariableType& res) const override;
private:
  T::JacobianFunctionType jac;

};

#endif /* JACOBIAN_HPP */
