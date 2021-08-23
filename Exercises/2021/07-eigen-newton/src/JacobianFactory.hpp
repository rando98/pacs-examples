#ifndef JACOBIANFACTORY_HPP
#define JACOBIANFACTORY_HPP

#include "Jacobian.hpp"

#include<memory>

enum class JacobianType
{
  Full,
  Discrete
};

template<class... Args> // variadic template, used because Discrete and FullJacobian uses different constructors parameters.
std::unique_ptr<JacobianBase>
make_jacobian(const JacobianType& type, Args... args)
{
  if constexpr (type == JacobianType::Discrete)
    return std::make_unique<DiscreteJacobian>(args...);
  else if constexpr (type == JacobianType::Full)
    return std::make_unique<FullJacobian>(args...);
}

#endif /* JACOBIANFACTORY_HPP */
