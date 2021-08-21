#ifndef DERIVATIVES_HPP
#define DERIVATIVES_HPP

#include<functional>

class BACKWARD; //

class FORWARD
{
public:
  using Other = BACKWARD; // SO I AM ABLE TO SWITCH BEETWEEN FORWARD AND BACKWARD WHILE CALCULATING THE ORDERS OF DERIVATIVE!
};

class BACKWARD
{
public:
  using Other = FORWARD;
};

template <unsigned int N, class FunctionType, class DifferenceType>
class NthDerivative
{
public:

  NthDerivative(const FunctionType& f, const double& h)
    : previous_derivative(f, h), h(h)
  {}

  double
  operator()(const double& x) const
  {
    if constexpr (std::is_same_v<DifferenceType, FORWARD>)
      return (previous_derivative(x+h) - previous_derivative(x)) / h;
    else
      return (previous_derivative(x) - previous_derivative(x-h)) / h;
  }
private:
  NthDerivative<N-1, FunctionType, typename DifferenceType::Other> previous_derivative;
  double h;
};

// Specialization for N=1
template<class FunctionType, class DifferenceType>
class NthDerivative<1, FunctionType, DifferenceType >
{
public:
  NthDerivative(const FunctionType& f, const double& h)
    : f(f), h(h)
  {};

  double
  operator()(const double& x) const
  {
  if constexpr (std::is_same_v<DifferenceType, FORWARD>)
    return (f(x+h) - f(x)) / h;
  else
    return (f(x) - f(x-h)) / h;
  }

private:
  FunctionType f;
  double h;
};

template<unsigned int N, class FunctionType>
auto // NthDerivative<N, FunctionType>
make_forward_derivative(const FunctionType& f,const double& h)
{
  return NthDerivative<N, FunctionType, FORWARD>(f, h);
}

template<unsigned int N, class FunctionType>
auto // NthDerivative<N, FunctionType>
make_backward_derivative(const FunctionType& f,const double& h)
{
  return NthDerivative<N, FunctionType, BACKWARD>(f, h);
}


#endif /* DERIVATIVES_HPP */
