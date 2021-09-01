#ifndef RKFTRAITS_HPP
#define RKFTRAITS_HPP

#include <functional>
#include <vector>
#include "Eigen/Dense"

class ProblemType
{
public:
  using Scalar = double;
  using Vector = Eigen::VectorXd; // but also std::vector<double> is ok!
};

template<class Type>
class RKFTraits
{
public:
  using VariableType = Type; // VariableType is for y. t is always a scalar!
  using FunctionType = std::function<Type(const double &, const Type&)>;
};

template<class T>
double
norm(const T& var)
{
  if constexpr (std::is_same_v<T, double>)
    return std::abs(var);
  else
    return var.norm();
}


/*
enum class RKFScheme : unsigned int
{
  RKF23 = 0,
  RKF45 = 1
};
*/


#endif /* RKFTRAITS_HPP */
