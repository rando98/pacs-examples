#include "NewtonTraits.hpp"
#include "JacobianFactory.hpp"

int
main(int argc, char **argv)
{
  using VariableType       = NewtonTraits::VariableType;
  using JacobianMatrixType = NewtonTraits::JacobianMatrixType;

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

  FullJacobian jac_full(jacobian_fun);

  const double h = 0.1;
  DiscreteJacobian jac_discrete(system, h);

  // jac_full.solve(x,b)

  auto jac = make_jacobian(JacobianType::Discrete, system, h);

  return 0;
}
