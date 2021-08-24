#ifndef NEWTON_HPP
#define NEWTON_HPP

#include "NewtonMethodsSupport.hpp"
#include "JacobianFactory.hpp"

class Newton
{
public:

  using T = NewtonTraits;

  Newton(const T::NonLinearSystemType& system_, std::unique_ptr<JacobianBase> jac_, NewtonOptions options_ = NewtonOptions())
    : system(system_), jac(std::move(jac_)), options(options_)
  {}

  Newton(const Newton&) = delete;

  NewtonResult
  solve(const T::VariableType& x0);

private:
  T::NonLinearSystemType system;
  std::unique_ptr<JacobianBase> jac; // not copy constructable => class Newton not copy consryctable
  NewtonOptions options;
  NewtonResult result;
};

#endif /* NEWTON_HPP_ */
