#ifndef DERIVATIVES_HPP
#define DERIVATIVES_HPP

#include<functional>

template <unsigned int N, class FunctionType>
class NthDerivative
{
public:

  NthDerivative(const FunctionType& f, const double& h)
    : previous_derivative(f, h), h(h)
  {}

  double
  operator()(const double& x) const
  {
    return previous_derivative(x+h) - previous_derivative((x)) / h;
  }
private:
  NthDerivative<N-1, FunctionType> previous_derivative;
  double h;
};

// Specialization for N=1
template<class FunctionType>
class NthDerivative<1, FunctionType>
{
public:
  NthDerivative(const FunctionType& f, const double& h)
    : f(f), h(h)
  {};

  double
  operator()(const double& x) const
  {
    return (f(x+h)-f(x)) / h;
  }

private:
  FunctionType f;
  double h;
};

template<unsigned int N, class FunctionType>
auto // NthDerivative<N, FunctionType>
make_forward_derivative(const FunctionType& f,const double& h)
{
  return NthDerivative<N, FunctionType>(f, h);
}

#endif /* DERIVATIVES_HPP */
