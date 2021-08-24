#ifndef NEWTONTRAITS_HPP
#define NEWTONTRAITS_HPP

#include "Eigen/Dense"
#include <functional>

enum class ProblemType
{
  Scalar, // problema scalare (mono-dimensionale)
  Vector // problema vettoriale (multi-dimensionale)
};

template <ProblemType Type>
class NewtonTraits
{};

template<> // Specialization
class NewtonTraits<ProblemType::Scalar>
{
public:
  using VariableType = double;
  using JacobianMatrixType = double;

  using NonLinearSystemType = std::function<VariableType(const VariableType&)>;
  using JacobianFunctionType = std::function<JacobianMatrixType(const VariableType&)>;

  static
  double
  compute_norm(const VariableType& x)
  {
    return std::abs(x);
  }

};

template<> // Specialization
class NewtonTraits<ProblemType::Vector>
{
public:
  using VariableType = Eigen::VectorXd; // Dynamic vector of double
  using JacobianMatrixType = Eigen::MatrixXd;

  using NonLinearSystemType = std::function<VariableType(const VariableType&)>;
  using JacobianFunctionType = std::function<JacobianMatrixType(const VariableType&)>;

  static
  double
  compute_norm(const VariableType& x)
  {
    return x.norm();
  }

};

#endif /* NEWTONTRAITS_HPP */
