#ifndef JACOBIANFACTORY_HPP
#define JACOBIANFACTORY_HPP

#include "Jacobian.hpp"

#include<memory>

enum class JacobianType
{
  Full,
  Discrete
};

template<JacobianType Type, class... Args> // variadic template, used because Discrete and FullJacobian uses different constructors parameters.
std::unique_ptr<JacobianBase>
make_jacobian(Args&&... args)
{
  if constexpr (Type == JacobianType::Discrete)
    return std::make_unique<DiscreteJacobian>(std::forward<Args>(args)...);
  else if constexpr (Type == JacobianType::Full)
    return std::make_unique<FullJacobian>(std::forward<Args>(args)...);
}

#endif /* JACOBIANFACTORY_HPP */
