#ifndef JACOBIANFACTORY_HPP
#define JACOBIANFACTORY_HPP

#include "Jacobian.hpp"

#include<memory>

enum class JacobianType
{
  Full,
  Discrete
};

template<ProblemType ProbType, JacobianType Type, class... Args> // variadic template, used because Discrete and FullJacobian uses different constructors parameters.
std::unique_ptr<JacobianBase<ProbType>>
make_jacobian(Args&&... args) // universal reference for Args, since type of Args is deduced at the moment of instance of the method  !!!!
{
  if constexpr (Type == JacobianType::Discrete)
    return std::make_unique<DiscreteJacobian<ProbType>>(std::forward<Args>(args)...); // forwarding the same value category of Args passed to the template
  else if constexpr (Type == JacobianType::Full)
    return std::make_unique<FullJacobian<ProbType>>(std::forward<Args>(args)...); // forwarding ...
}

#endif /* JACOBIANFACTORY_HPP */
