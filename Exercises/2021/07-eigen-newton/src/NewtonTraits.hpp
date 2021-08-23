#ifndef NEWTONTRAITS_HPP
#define NEWTONTRAITS_HPP

#include "Eigen/Dense"
#include <functional>

class NewtonTraits
{
public:
  using VariableType = Eigen::VectorXd; // Dynamic vector of double
  using JacobianMatrixType = Eigen::MatrixXd;

  using NonLinearSystemType = std::function<VariableType(const VariableType&)>;
  using JacobianFunctionType = std::function<JacobianMatrixType(const VariableType&)>;
};

#endif /* NEWTONTRAITS_HPP */
