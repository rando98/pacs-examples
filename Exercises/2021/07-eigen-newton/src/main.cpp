#include <iostream>

#include "NewtonTraits.hpp"
#include "JacobianFactory.hpp"
#include "Newton.hpp"

int
main(int argc, char **argv)
{
  constexpr ProblemType Type = ProblemType::Vector;

  using VariableType       = NewtonTraits<Type>::VariableType; // In using I don't have to specify the keyword typename since the compiler will do it for me
  using JacobianMatrixType = NewtonTraits<Type>::JacobianMatrixType;

  auto system = [](const VariableType &x) -> VariableType {
    VariableType y(2);

    y(0) = (x[0] - 1) * (x[0] - 1) + 0.1 * (x[1] - 5) * (x[1] - 5);
    y(1) = 1.5 - x[0] - 0.1 * x[1];

    return y;
  };

  auto jacobian_fun = [](const VariableType &x) -> JacobianMatrixType {
    JacobianMatrixType J(2, 2);

    J(0, 0) = 2 * (x[0] - 1);
    J(0, 1) = 0.2 * (x[1] - 5);
    J(1, 0) = -1;
    J(1, 1) = -0.1;

    return J;
  };

  FullJacobian<Type> jac_full(jacobian_fun);

  const double h = 0.1;
  DiscreteJacobian<Type> jac_discrete(system, h);

  // jac_full.solve(x,b)

  auto jac = make_jacobian<Type, JacobianType::Discrete>(system, h);

   // auto jac2 = make_jacobian<JacobianType::Full>(jacobian_fun);

  // To pass the unique pointer we can either create it when creating the newton object (see Newton newton(...))
  // or usign std::move (see Newton quasi_newton(...))
  // (We could also use pass by reference but in this way we cannot bind it on a temporary object!)
  Newton newton(system, make_jacobian<Type, JacobianType::Full>(jacobian_fun));

  VariableType x0(2);
  auto result = newton.solve(x0);

  std::cout << "Solution: [" << result.solution[0] << "," << result.solution[1] << "]" << std::endl;

  Newton quasi_newton(system, std::move(jac)); // The jac pointer is invalid now.

  return 0;
}
